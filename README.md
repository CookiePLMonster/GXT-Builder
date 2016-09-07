# GXT Builder
GXT Builder for GTA Vice City and GTA San Andreas.

This tool allows you to build GXT files from UTF-8 text files. It also contains a simple version control system for easy managing of translations.

## Building

Visual Studio 2015 is recommended, though Visual Studio 2013 should work just fine too.

## Using

    gxtbuilder path\to\ini.ini [-vc] [-sa] [additional langs...]

The tool requires a specific INI file formatting. Please look up `doc\american.ini` for a documentation of the used INI format.

## Advanced Usage

**GXT Builder** contains a simple inbuilt version control for translations. When building a primary language, 
you can specify names of other language files in `additional langs...` list. 
Upon building the primary language, the program creates a cache file which stores information about all texts from this language.
On next builds, if the builder detects any differences between cached data and currently build texts, it'll output a message for all
non-primary languages (basing on the provided list). All modified and added text lines are output to `[langname]_changes.txt`, so it's possible
to keep track of all changes in the primary language and then update a translation.

Upon building a non-primary language, the builder checks if there are any entries in `[langname]_changes.txt` and forbids the user from
building the GXT if there are any entries found. Therefore, the user should audit all the entries from `[langname]_changes.txt` and
ensure the translation is stil in line with an updated primary language text line. When this is done and `[langname]_changes.txt`
is emptied, the GXT builds as usual.

## Help

For additional help, use:

    gxtbuilder --help
