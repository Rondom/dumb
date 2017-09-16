# Dynamic Universal Music Bibliotheque (libdumb)

     _______         ____    __         ___    ___
    \    _  \       \    /  \  /       \   \  /   /       '   '  '
     |  | \  \       |  |    ||         |   \/   |         .      .
     |  |  |  |      |  |    ||         ||\  /|  |
     |  |  |  |      |  |    ||         || \/ |  |         '  '  '
     |  |  |  |      |  |    ||         ||    |  |         .      .
     |  |_/  /        \  \__//          ||    |  |
    /_______/ynamic    \____/niversal  /__\  /____\usic   /|  .  . ibliotheque
                                                         /  \
                                                        / .  \
                                                       / / \  \
                                                      | <  /   \_
                                                      |  \/ /\   /
                                                       \_  /  > /
                                                         | \ / /
                                                         |  ' /
                                                          \__/



## Introduction

DUMB is a module audio renderer library. It reads module files and
outputs audio that can be dumped to the actual audio playback library.

## Features

- Supports playback of IT, XM, S3M, MOD, 669, AMF, ASY, MOD, MTM, OKT,
  PSM (old and new), PTM, RIFF, STM files

- Audio generated can be used in any way; DUMB does not necessarily send it
  straight to a sound output system

- Portable

- Faithful to the original trackers, especially IT; if it plays a module
  wrongly, it is considered a bug

- Accurate support for low-pass resonant filters for IT files

- Very accurate timing and pitching; completely deterministic playback

- Click removal

- Three resampling quality settings: aliasing, linear interpolation and cubic
  interpolation

- Number of samples playing at once can be limited to reduce processor usage,
  but samples will come back in when other louder ones stop

- Option to take longer loading but seek fast to any point before the music
  first loops (seeking time increases beyond this point)

- All notes will be present and correct even if a module's playback is started
  in the middle

- Optional Allegro4 integration support

- Facility to embed music files in other files (e.g. Allegro datafiles)


## Installation

Currently you need to compile libdumb yourself. For more details, please see
the file [COMPILING.md](COMPILING.md).

## License

See [LICENSE](LICENSE) for license details.

## Contributing

Bugs, feature requests and patches can be submitted at https://github.com/kode54/dumb/.
