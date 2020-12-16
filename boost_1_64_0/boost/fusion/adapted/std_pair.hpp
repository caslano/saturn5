/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STD_PAIR_HPP
#define BOOST_FUSION_ADAPTED_STD_PAIR_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <utility>

BOOST_FUSION_ADAPT_TPL_STRUCT(
    (T1)(T2),(std::pair)(T1)(T2),(T1, first)(T2, second))

#endif

/* std_pair.hpp
nkPvIZ5Ij+KogabojIGYjZXYh3O4DbmX/RJSIQeKoQqaoQdGYgE24xRu4z0S7iNHkA810Q3DMA1/YQN24gjO4w7EfuogPkVKZEZeVEQTdEB/jMN8rMQOHMFVPMATRAeIHZLge2RAEVRBE3TFEEzBcuzAGdxBdJD5i++QGWVQG43RBYMxAQuwFttxABfxGO4Q44UfkQHF8SsaowP6YjKWYhfO4T7EYeY/kiM3fkFj9MAIzMZy7MF5PEU4Qh1ALPKiIpqiN8ZhETbiKM7iFl4h8VHahlJohkGYi404hpuwx+gDCqE+umMMFmEVtuEU7uA9Eh0n3siMIvgFTdEVgzABi7ASh3EGN/EE7/H5CdZeFENlNEQn9MZYzMEaHMZ1PIM/ybqLdMiKkqiEJuiCoZiB5diB83gMeYr8QTKkRUnUQGv0wHBMwTJsxDYcxGncwBO8hj/N5+Ab/ISMyItyqIWGaIueGIoxmIEl2IQDuIB7eIv4Z9g/IzmyojgqojbaYSBGYxqWYAfO4TZeIu5ZznbIjOKog3boj9GYhoXYjCP4Dw9gzpEr+AnpkB0lUA1N0Q2jsRDbcAy3Ic+Tq0iP4qiOluiFsZiHfbiGt0h6gbxGUdRAG/TDVKzGIfyHF4h7kfggG0qiAbpjDOZgJXbhKK7gPtQl5iF+RE5URjP0xHDMxWocwL+4g7dI+C/3IAtKohY6YgwWYiNO4DreI+llrkceVEQ3jMdKHMIdxFyhhiAPaqMTRmAKFmArjuMWnsFfZR1DBpRAfXTGEEzHVlzAc8T8x7qEHCiDhuiAPzAFq7AX1yCusRYjG8qhIfpgApZjP67iJeJdp83IgGKoix4YgyXYjUt4inCDz0UWlEEDdMIfmIqVOIAbiG4yZvgJOVAE1dAY7dEHQzAOM7Ace3ABD2FvMc+QArlRHvXQFN0xErOxFgdxFXcgb/O9+AE5UAZ10BH9MRHzsBHHcQNv8eEd4osiqI7W6I8pWI5juIl3MHe5Hl8iPfKhDGqgObpiMMZgGuZjAw7gPO7B3iNvkQmlUQNt0B+T8Bd24xzuILrP76b4EmmRG2VQH+0xCFOwCjtxDc8R7wHrIbKhLOqgMwZiMpZgO87gDqKH1AV8h4wogkpogHboizGYieXYiuO4hegRew1kRUX8hm4Yi2XYi/N4gPCYXEcmFEYVNEI79MFYzMUaHMQVvESCJ+QMMiIfKqIe2qIXhmE2NuAkHiA8Zd4iIwqhBtpjFBZgE47hDtQzzg3IiGKojt/QEX0xGnOwCafxFPGfM17IisKogobogP6YiH9wHDfwBklfsOdHUfyK5hiEGViPfTiD+4h5yXxGTpRCTbREX4zFHKzDGbxAklesJ8iFSmiNvpiAxdiJy3iGhK+pzyiECmiCrhiEP7EUW3ESjxDvDW1BHpRGHbRANwzDNCzHbpzEDbxD0rfsJ1EYldABI7EQa7Ebl/AQ4h01HT8hMwqjEpqjB0ZjDjbgBO7CvSc3kA5FUAVN0Q3DMAPrcRIPEXgw3XfIjQqoh1YYgLFYiG04hYdQIjb6HBlQAo3QE6OxFHtwEbfxAk7GRp8gBQqhKtpiIMZhPtZiL/7DKyRSsdG3yICyaI0RmIOtuIhIx0afIT3yowLaYiT+xBKsx26cwF0IXrD0KdKjPNpjOJbiEG7B29joG2RHBbTAEMzHTlyHc/QHBVEf3TEFq3EOz5HY036UR1uMxV84gMt4io9CbJQKBVETvTANW3EWr5GEf0pKjcJogF6YiJU4gOsQcWKjL5EOBVAVjdEb4/EX9uAaZFz6hywojQboicn4BwdwHSJebJQQXyEjSqIBemMqNuIEHsPHj43+h/QohnroiUlYjl0=
*/