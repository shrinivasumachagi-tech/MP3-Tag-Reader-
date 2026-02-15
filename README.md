#🎵 MP3 Tag Reader (ID3v2.3) in C

A simple and efficient C-based project to read, display, and edit MP3 metadata using the ID3v2.3 tag format.

This project demonstrates core C programming concepts such as binary file handling, structures, string processing, pointer usage, and metadata parsing.

📌 Project Overview

MP3 files not only store audio data but also contain metadata known as ID3 tags. These tags store information like:

🎶 Title

🎤 Artist

💿 Album

📅 Year

🎧 Genre

📝 Comments

This project reads and extracts these details directly from the MP3 file without modifying the audio data.

🚀 Features

✅ Validate ID3v2.3 header

✅ Parse MP3 frame structure

✅ Extract metadata fields

✅ Display song details

✅ Edit selected tags (Title, Artist, Album, etc.)

✅ Clean modular implementation

🛠 Technologies Used

C Programming

GCC Compiler

File I/O (Binary Mode)

Structures

String handling functions (strncmp, strcmp)

Big-endian conversion logic

📂 Project Structure
SHRINIVAS_MP3_TAG_READER/
│── main.c        → Driver program
│── id3v2.h       → ID3v2 structure definitions
│── id3v2.c       → Core ID3v2 parsing logic
│── mp3view.c     → View metadata implementation
│── mp3edit.c     → Edit metadata implementation
│── mp3tag.h      → Tag structure definitions
│── common.h      → Common macros and utilities
│── sample.mp3    → Test MP3 file
│── a.out         → Compiled output file


🧠 Key Concepts Implemented

Binary file handling using fopen("rb")

File pointer manipulation using fseek

Header validation using strncmp

Frame parsing (10-byte frame header)

Big-endian to integer conversion

Structure-based metadata storage

🏗 ID3v2.3 Structure
🔹 Header (10 Bytes)

"ID3" identifier

Version number

Flags

Tag size

🔹 Frame Structure

Each frame contains:

Frame ID (e.g., TIT2, TPE1)

Frame Size

Flags

Data

▶️ How to Compile & Run
Compile
gcc main.c id3v2.c mp3view.c mp3edit.c -o mp3tag


Run
./mp3tag


Make sure sample.mp3 is in the same directory.

🖥 Sample Output
====== SONG DETAILS ======
Title   : Steganography
Artist  : Shrinivas
Album   : C Project
Year    : 2026
Genre   : Test
Comment : MP3 ID3v2 tag testing
==========================

📚 Applications

Media player development

Digital audio tools

Metadata management systems

Learning binary file parsing

Academic mini-projects

⚠ Limitations

Supports only ID3v2.3

Limited Unicode support

Basic in-place editing

🔮 Future Enhancements

Support ID3v2.4

Add album art extraction

Unicode support

GUI interface

Multi-file batch processing

🎯 Project Purpose

This project was developed as part of hands-on training at Emertxe Information Technologies.
It focuses on implementing real-time MP3 metadata parsing using C programming.

The project strengthens practical understanding of:

Binary file handling

Low-level data processing

MP3 file structure and ID3v2.3 tag format

Frame parsing and metadata extraction

Structured and modular C programming

This implementation reflects real-world file parsing techniques used in multimedia applications.

👨‍💻 Author

Shrinivas Raju Umachagi
B.E. Electronics & Communication Engineering
