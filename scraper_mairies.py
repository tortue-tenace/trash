#!/usr/bin/env python3

import re
import time
import logging
import requests
from bs4 import BeautifulSoup
from pathlib import Path

BASE_URL = "https://www.adresses-mairies.fr"
OUTPUT_FILE = "emails_mairies.txt"
DELAY = 0.5  # secondes entre chaque requête pour ne pas surcharger le serveur

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    handlers=[
        logging.FileHandler("scraper_mairies.log"),
        logging.StreamHandler(),
    ],
)
log = logging.getLogger(__name__)

SESSION = requests.Session()
SESSION.headers.update({
    "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
                  "(KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"
})


def get_soup(url: str) -> BeautifulSoup | None:
    try:
        resp = SESSION.get(url, timeout=15)
        resp.raise_for_status()
        return BeautifulSoup(resp.text, "html.parser")
    except requests.RequestException as e:
        log.warning(f"Erreur lors de la récupération de {url}: {e}")
        return None


def get_department_urls() -> list[str]:
    """Récupère les URLs de tous les départements depuis la page d'accueil."""
    soup = get_soup(BASE_URL)
    if not soup:
        return []

    dept_links = []
    for a in soup.find_all("a", href=True):
        href = a["href"]
        # Les pages de département suivent le pattern /departement-{nom}-{num}.html
        if re.match(r"^/departement-[a-z0-9-]+-\d+\.html$", href):
            url = BASE_URL + href
            if url not in dept_links:
                dept_links.append(url)

    log.info(f"{len(dept_links)} départements trouvés")
    return dept_links


def get_commune_urls(dept_url: str) -> list[str]:
    """Récupère les URLs de toutes les communes d'un département."""
    soup = get_soup(dept_url)
    if not soup:
        return []

    commune_links = []
    for a in soup.find_all("a", href=True):
        href = a["href"]
        # Les pages de mairie suivent le pattern /mairie-de-{nom}-{id}.html
        if re.match(r"^/mairie-[a-z0-9-]+-\d+\.html$", href):
            url = BASE_URL + href
            if url not in commune_links:
                commune_links.append(url)

    return commune_links


def get_email(commune_url: str) -> tuple[str, str] | tuple[None, None]:
    """Extrait le nom de la mairie et son e-mail depuis la page de la commune."""
    soup = get_soup(commune_url)
    if not soup:
        return None, None

    # Nom de la mairie
    name = ""
    h1 = soup.find("h1")
    if h1:
        name = h1.get_text(strip=True)

    # E-mail via le lien mailto:
    mailto = soup.find("a", href=re.compile(r"^mailto:"))
    if mailto:
        email = mailto["href"].replace("mailto:", "").strip()
        return name, email

    return name, None


def main():
    log.info("=== Démarrage du scraper mairies ===")

    dept_urls = get_department_urls()
    if not dept_urls:
        log.error("Aucun département trouvé. Arrêt.")
        return

    output_path = Path(OUTPUT_FILE)
    # Chargement des URLs déjà traitées pour reprendre en cas d'interruption
    processed_communes: set[str] = set()
    if output_path.exists():
        with open(output_path, "r", encoding="utf-8") as f:
            for line in f:
                parts = line.strip().split("\t")
                if len(parts) >= 3:
                    processed_communes.add(parts[2])  # URL en 3e colonne
        log.info(f"{len(processed_communes)} communes déjà traitées (reprise)")

    total_emails = 0
    total_communes = 0

    with open(output_path, "a", encoding="utf-8") as out:
        for dept_idx, dept_url in enumerate(dept_urls, 1):
            dept_name = dept_url.split("/")[-1].replace(".html", "")
            log.info(f"[{dept_idx}/{len(dept_urls)}] Traitement : {dept_name}")

            commune_urls = get_commune_urls(dept_url)
            log.info(f"  → {len(commune_urls)} communes trouvées")
            time.sleep(DELAY)

            for commune_url in commune_urls:
                if commune_url in processed_communes:
                    continue

                total_communes += 1
                name, email = get_email(commune_url)
                time.sleep(DELAY)

                if email:
                    total_emails += 1
                    line = f"{name}\t{email}\t{commune_url}\n"
                    out.write(line)
                    out.flush()
                    log.debug(f"  ✓ {name}: {email}")

    log.info(f"=== Terminé : {total_emails} e-mails récupérés sur {total_communes} communes ===")
    log.info(f"Résultats sauvegardés dans : {OUTPUT_FILE}")


if __name__ == "__main__":
    main()
