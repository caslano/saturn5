//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o to Boost

#ifndef BOOST_CHRONO_IO_DURATION_STYLE_HPP
#define BOOST_CHRONO_IO_DURATION_STYLE_HPP

#include <boost/detail/scoped_enum_emulation.hpp>

namespace boost
{
  namespace chrono
  {
    /**
     * Scoped enumeration emulation stating whether the duration I/O style is long or short.
     * prefix means duration::rep with whatever stream/locale settings are set for it followed by a long name representing the unit
     * symbol means duration::rep with whatever stream/locale settings are set for it followed by a SI unit abbreviation
     */
    BOOST_SCOPED_ENUM_DECLARE_BEGIN(duration_style)
          {
            prefix, symbol
          }
    BOOST_SCOPED_ENUM_DECLARE_END(duration_style)


  } // chrono

}

#endif  // header

/* duration_style.hpp
viBtEcgz2eRLNVkPenMduBQYB+wDTGKcv0udKfDpf9fEF50LWKTGhfpJgC4m47Kb4/I8MITxRozHAn8NTADu5bx9AZjO/FbAamA74D5gZ+B+NS7U/bGQ93f83QO8Xl7R8eUE4JvGdk5nO2cAeT1Qx0Xq5vheD9JHTktgArA/sAlwKDAVWAJsBpwFbA58ENgCWAlsB6wCtgL+Ftga+BKwDbAG2BZ4HJgIdDpkefqOoh4HdU3CfXxHdeT13YXz/yKu25nAI4x/AOwG/AjYHXiO+Z0c0gcP5xW//wNbmsyrng7OK2A8sA/H7zJdf5eQP9ykv7ezv5+kj74dQPLhm7f1ffEp8u3iffFp8j0n+I2a37nBJ++PO3W2CZKB8cDOwET64EuiL6lk+ujqDpxA2ypLgBnACmBL4AO0rfJz4IXAl4AX05dUN2AN+f8GbAf8jjY10hxY54GdgR2BlwO7Aq8Adle2Ovgtmc/u4T62Oj7hvP4rMBR4gtfTZ7wffAqMZtxTX1aA+vryOaEfMBR4BTAC2B8YCcwCRjPuqS8nQH0DWd8g1jeY9WWzvqtYH+K83/EbLPBWk/tdJefVY1wftgKbAp/hfe0JYC/gk8As4A5gNvBnwJHAncDrgbuAucCngQXAKuBU1uOZ56cpRw+Ted4P5RoDrwDGAfsDuwIHAfk8xe+IaI/J89QqtuM+tmMNMBW4iffltbxOH+Dz5YO8XtfxOXM9n7c2AK8DbgTeQP4vtXzB73nAVM77WO1bEH//C96f/wG8FPgNfU1+C7wZ+D1wGlCgvns1AK4DRgMfBYYAdwHD+BzbCPg8MAL4G2Ak8AOW/wz4tcB4O2Sc8vGbFbCViXzP0qfdL4H96XttKHAvsARYDZwF3MfnhReBlcBDwCrgy8Df0nfbfuArwFeBIHlff43X40HgKeAeYIwD/HqbQ2ut77sPcb3ZwPvuRr3NoQB8m8m3hXyV+ueDAHyjyTeGfMr2C78vWN3nu/M+34P3+UuASYyr5+e11ve/e/m7q4Au2vBRzwcB+G4iXy758rx8mNTW7TzF9ezvfD74HEg+7Adb/95r5DvI+/shHV9GAL7JlHMK5bxFyQkiX5jZewX5lgFD6eNRra/ku9xkPZxNWzi3AdvSt2t7+pbsAlwA7MW4moesL9lEjlLWVw6M09nM2g6qIl8Er694bX0g32FeX29Rjrcpx9/5nH4UOJo+bW8Dfsjn9OPAVcC/8P73CZ/TTwAfA34K3AH8G/Bp4Enga8BTwEP0ofs5feie4e+x37j3hTXUpN9yOI9HAeOB1wKbA8cCLwFeB8wCjgMqm1KsL8PkuhjG+oYDU4AjgGmMr6QvvYNHImFvKLAfve0/MTtDhaDR/+N2hsxsDJ3EWEYfjRSdQTmgyaCloO2gl0A1oLOgxHfhVw80DlQOWguqAh0GnQEl/gl1gLJBhaBFoK2gvaC3QGdATd6LFJmg4aBC0DzQWtBu0FHQGVDiMZQBDQdNBq0E7QQdBJ0AifdRD6jH+7YtIzvYwQ52sIMd7GAHO9jBDnaww49m/w9H6Opv/685fONVaHrt+MDnElK9shyG4WZOL5C+RmT+fcjPTNblU5G0jH7/BtF+IHUzZBjAbw/96G+i5m6p1zRo1Kjc4hn5hbmsCbKUKV2qF1HDfkm16zB59JXCHXXXM6qr/svja2T92c3m9S35LvFcca+7nz3iXGuld2OlL2Olr9Rw/h64Z8e+lmOAaWHcsyvn3uRsYDPgHNqTn8tvDvOA/Wh/f6XGfwr7NaAenbmXxn20bJ89stHcA2vPPa+jIP2+ViH3rM6A9PtT3HtSe05NuLfku59Uecrec7GDHexgBzvYwQ52sIM=
*/