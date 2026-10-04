#pragma once

/// \file string.h
/// \brief Laengenbegrenzte Zeichenpuffer, Pfade und Verzeichnisse.

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/// \brief Groesse eines string_t-Puffers in Bytes (einschliesslich Nullbyte).
#define STRING_MAXLEN 4096

/// \brief Rueckgabewert von string_copy/string_cat, wenn der Zielpuffer zu klein ist.
#define STRING_ERROR -1

/// \brief Fester Zeichenpuffer der Bibliothek — laengenbegrenzt, kein Heap.
typedef char string_t[STRING_MAXLEN];

/// \brief Kopiert source nach destination.
/// \param destination Zielpuffer.
/// \param destinantion_size_bytes Groesse des Zielpuffers in Bytes.
/// \param source Quelltext (nullterminiert).
/// \return 0 bei Erfolg; STRING_ERROR, wenn der Zielpuffer kleiner als strlen(source) ist (das Ziel
///         bleibt dann unveraendert).
int32_t string_copy(char* destination, size_t destinantion_size_bytes, const char* source);

/// \brief Haengt source an destination an.
/// \param destination Zielpuffer mit vorhandenem Inhalt.
/// \param destinantion_size_bytes Groesse des Zielpuffers in Bytes.
/// \param source anzuhangender Text.
/// \return 0 bei Erfolg; STRING_ERROR, wenn strlen(destination) + strlen(source) nicht mehr in den
///         Puffer passt (das Ziel bleibt dann unveraendert).
int32_t string_cat(char* destination, size_t destinantion_size_bytes, const char* source);

/// \brief Verzeichnisanteil eines Dateipfads (wie dirname).
/// \param filepath Pfad — WIRD VERAENDERT.
/// \return Zeiger INNERHALB von filepath auf den Verzeichnisanteil; der Pfad ist danach nicht mehr
///         als Ganzes brauchbar.
const char* string_dirname_from_filepath(char* filepath);

/// \brief Pfad der laufenden Binaerdatei (/proc/self/exe).
/// \param exe_path Zielpuffer.
/// \param buffer_size Groesse des Zielpuffers in Bytes.
/// \note Ist der Pfad nicht lesbar, steht danach "unknown" im Puffer.
void string_get_exe_path(char* exe_path, size_t buffer_size);

/// \brief Existiert der Pfad?
/// \param directory Pfad.
/// \return true, wenn stat gelingt — auch fuer DATEIEN, nicht nur Verzeichnisse.
bool string_directory_exists(const char* directory);

/// \brief Legt das Verzeichnis an (Modus 0700).
/// \param directory Pfad.
/// \note Ein bereits vorhandenes Verzeichnis ist kein Fehler.
void string_directory_create(const char* directory);

/// \brief Existiert der Pfad?
/// \param filepath Pfad.
/// \return true, wenn der Zugriff (access, F_OK) gelingt — Datei oder Verzeichnis.
bool string_filepath_exist(char* filepath);

/// \brief Haengt directory an path an ("path/directory") und legt das Ergebnis an, falls es fehlt.
/// \param path Basispfad.
/// \param directory anzuhangendes Verzeichnis.
/// \return Zeiger auf einen STATISCHEN Puffer — beim naechsten Aufruf ueberschrieben.
const char* string_append_directory_to_path_and_create(const char* path, const char* directory);

/// \brief Erste Fundstelle von sub_string in string.
/// \param string durchsuchter Text.
/// \param sub_string gesuchter Text.
/// \return Index der ersten Fundstelle, sonst -1.
int32_t string_calculate_substring_index(const char* string, const char* sub_string);

/// \brief Setzt die Textcursor-Position (ANSI).
/// \param x Spalte (1-basiert).
/// \param y Zeile (1-basiert).
/// \note Nur fuer ein Terminal.
void string_set_cursor_position(int x, int y);

/// \brief Leert den Bildschirm und setzt den Cursor nach Hause (ANSI).
/// \note Nur fuer ein Terminal.
void string_clear_screen();

/* ---------- Vordergrundfarben (Standard) ---------- */
#define COLOR_BLACK     "\x1b[30m"
#define COLOR_RED       "\x1b[31m"
#define COLOR_GREEN     "\x1b[32m"
#define COLOR_YELLOW    "\x1b[33m"
#define COLOR_BLUE      "\x1b[34m"
#define COLOR_MAGENTA   "\x1b[35m"
#define COLOR_CYAN      "\x1b[36m"
#define COLOR_WHITE     "\x1b[37m"
#define COLOR_RESET     "\x1b[0m"

/* ---------- Vordergrundfarben (Hell/Bright) ---------- */
#define COLOR_BRIGHT_BLACK     "\x1b[90m"
#define COLOR_BRIGHT_RED       "\x1b[91m"
#define COLOR_BRIGHT_GREEN     "\x1b[92m"
#define COLOR_BRIGHT_YELLOW    "\x1b[93m"
#define COLOR_BRIGHT_BLUE      "\x1b[94m"
#define COLOR_BRIGHT_MAGENTA   "\x1b[95m"
#define COLOR_BRIGHT_CYAN      "\x1b[96m"
#define COLOR_BRIGHT_WHITE     "\x1b[97m"

/* ---------- Hintergrundfarben (Standard) ---------- */
#define BG_BLACK    "\x1b[40m"
#define BG_RED      "\x1b[41m"
#define BG_GREEN    "\x1b[42m"
#define BG_YELLOW   "\x1b[43m"
#define BG_BLUE     "\x1b[44m"
#define BG_MAGENTA  "\x1b[45m"
#define BG_CYAN     "\x1b[46m"
#define BG_WHITE    "\x1b[47m"

/* ---------- Hintergrundfarben (Hell/Bright) ---------- */
#define BG_BRIGHT_BLACK     "\x1b[100m"
#define BG_BRIGHT_RED       "\x1b[101m"
#define BG_BRIGHT_GREEN     "\x1b[102m"
#define BG_BRIGHT_YELLOW    "\x1b[103m"
#define BG_BRIGHT_BLUE      "\x1b[104m"
#define BG_BRIGHT_MAGENTA   "\x1b[105m"
#define BG_BRIGHT_CYAN      "\x1b[106m"
#define BG_BRIGHT_WHITE     "\x1b[107m"

/* ---------- Textformatierungen ---------- */
#define TEXT_BOLD     "\x1b[1m"
#define TEXT_DIM      "\x1b[2m"     ///< Verblasst
#define TEXT_ITALIC   "\x1b[3m"     ///< Kursiv (nicht überall unterstützt)
#define TEXT_UNDER    "\x1b[4m"
#define TEXT_BLINK    "\x1b[5m"     ///< Blinkend
#define TEXT_REVERSE  "\x1b[7m"     ///< Vorder-/Hintergrund tauschen
#define TEXT_HIDDEN   "\x1b[8m"     ///< Versteckt
#define TEXT_STRIKE   "\x1b[9m"     ///< Durchgestrichen

/* ---------- Cursor-Bewegung ---------- */
#define CURSOR_UP(n)     "\x1b[" #n "A"
#define CURSOR_DOWN(n)   "\x1b[" #n "B"
#define CURSOR_RIGHT(n)  "\x1b[" #n "C"
#define CURSOR_LEFT(n)   "\x1b[" #n "D"
#define CURSOR_HOME      "\x1b[H"
#define CURSOR_SAVE      "\x1b[s"
#define CURSOR_RESTORE   "\x1b[u"

/* ---------- Bildschirm löschen ---------- */
#define CLEAR_SCREEN     "\x1b[2J"
#define CLEAR_LINE       "\x1b[2K"
#define CLEAR_TO_EOL     "\x1b[0K"   ///< Bis zum Zeilenende
#define CLEAR_TO_BOL     "\x1b[1K"   ///< Bis zum Zeilenanfang

/* ---------- 256-Farben-Modus ---------- */
#define COLOR_256(n)     "\x1b[38;5;" #n "m"
#define BG_256(n)        "\x1b[48;5;" #n "m"

/* ---------- RGB-Farben (24-bit True Color) ---------- */
#define COLOR_RGB(r,g,b) "\x1b[38;2;" #r ";" #g ";" #b "m"
#define BG_RGB(r,g,b)    "\x1b[48;2;" #r ";" #g ";" #b "m"

/* ============================================================
   Hilfsmakros für kombinierte Formatierungen
   ============================================================ */

/// Kombinierte Farben + Formatierung
#define BOLD_RED        TEXT_BOLD COLOR_RED
#define BOLD_GREEN      TEXT_BOLD COLOR_GREEN
#define BOLD_YELLOW     TEXT_BOLD COLOR_YELLOW
#define BOLD_BLUE       TEXT_BOLD COLOR_BLUE
#define BOLD_MAGENTA    TEXT_BOLD COLOR_MAGENTA
#define BOLD_CYAN       TEXT_BOLD COLOR_CYAN
#define BOLD_WHITE      TEXT_BOLD COLOR_WHITE

/// Mit Hintergrund
#define RED_ON_WHITE    COLOR_RED BG_WHITE
#define BLACK_ON_WHITE  COLOR_BLACK BG_WHITE
#define BLUE_ON_WHITE   COLOR_BLUE BG_WHITE
#define GREEN_ON_BLACK  COLOR_GREEN BG_BLACK
#define YELLOW_ON_RED   COLOR_YELLOW BG_RED
#define WHITE_ON_BLUE   COLOR_WHITE BG_BLUE
#define BLACK_ON_GREEN  COLOR_BLACK BG_GREEN
#define BLACK_ON_YELLOW COLOR_BLACK BG_YELLOW

/* ---------- Einfache Nutzungsbeispiele ---------- */

/*
  // Einfache Farben
  printf(COLOR_RED "Roter Text" COLOR_RESET "\n");
  printf(COLOR_GREEN "Grüner Text" COLOR_RESET "\n");
  printf(COLOR_BRIGHT_BLUE "Helles Blau" COLOR_RESET "\n");

  // Formatierungen
  printf(TEXT_BOLD "Fetter Text" COLOR_RESET "\n");
  printf(TEXT_UNDER "Unterstrichen" COLOR_RESET "\n");
  printf(TEXT_BOLD COLOR_RED "Fett & Rot" COLOR_RESET "\n");

  // Hintergrund
  printf(BG_YELLOW COLOR_RED "Rot auf Gelb" COLOR_RESET "\n");
  printf(BG_BRIGHT_GREEN COLOR_BLACK "Schwarz auf Hellgrün" COLOR_RESET "\n");

  // 256-Farben (z.B. 214 = Orange)
  printf(COLOR_256(214) "Orange" COLOR_RESET "\n");
  printf(BG_256(27) COLOR_256(15) "Weiß auf Blau" COLOR_RESET "\n");

  // RGB True Color
  printf(COLOR_RGB(255,128,0) "Orange" COLOR_RESET "\n");
  printf(BG_RGB(0,100,200) COLOR_RGB(255,255,255) "Weiß auf Blau" COLOR_RESET "\n");

  // Cursor-Bewegung
  printf(CURSOR_SAVE "Text speichern" CURSOR_RESTORE "\n");
  printf(CURSOR_UP(2) "Zwei Zeilen hoch" CURSOR_DOWN(1) "Eine runter\n");

  // Bildschirm löschen
  printf(CLEAR_SCREEN "Bildschirm gelöscht\n");
  printf(CLEAR_LINE "Aktuelle Zeile gelöscht\n");

  // Hilfsmakros
  printf(BOLD_RED "Fett & Rot" COLOR_RESET "\n");
  printf(WHITE_ON_BLUE "Weiß auf Blau" COLOR_RESET "\n");
  printf(BLACK_ON_YELLOW "Schwarz auf Gelb" COLOR_RESET "\n");
*/
