
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_TYPEOF_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_TYPEOF_HPP_

#include <boost/local_function/aux_/symbol.hpp>

// PUBLIC //

// Actual type-name for specified symbol name.
#define BOOST_LOCAL_FUNCTION_AUX_TYPEOF_TYPE(name) \
    /* cannot prefix in front of name because it could start with non */ \
    /* alphanumeric symbols (e.g., & for binding by reference) */ \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL_POSTFIX( (name)(typeof_type) )

#endif // #include guard


/* typeof.hpp
SMr6IckTL7/xCc79Yaj0h/uUm3Z6dZ7blm76PsIx8pnkLWcHuvmNMbtN1cRtYta7ynfK/ob2tVbYqo/Dv/W5cmFSphuV/VC9GCkbhCZBa72MvPPq2s/K7hfSMQabsqrvuErfsVX8WL0rl4LPK/umerjOuyJSxIh7ovF7l/yweh822Y017BYquxBjb+4bKrwxpBl7I13vqnTNotaeJu/BkubRyu8wxhYts//WSt93UvlvpMt5h0bf1x+eIwED4SDpA/vaKW3K19zn5fF3mPo1n38oe7eKmZxb2kOlGb2uys7tcJtEki7tcAV8ifJO2+Joh9OSx6aOdGqHYdIu9io34/U6tMFu/PYMRyzb4hajfdCJ5XgWJ25d2iJuyYJxxu1mZX8XMXnz9rdOC9DHW7fJLdZt0qgfZT/AtX0ZZ2s+o+zj9EjaVlt+G/sjpjYm7Ze4ttrdeelv0D6+1fykPdHqlHkRc9sz3usbKLs3CGOdmOlaaWV2m8aTkb1NyTNxXKVpiN6YNuXv0qYGSxt6KSjrt7WvyPmgXNtX55zaV5C6p86ytS/qxqVf2ymHHz4qY+90GXsHPqbaU8rY0Yy8ncdqRj9TS7mZr+/QTli0IwmDf+76hEbKfpoexXRJdz00xzFaK+W2iDHuv13dT9UtxmxGv9tFuRmhR+jFtdaI1bitNIxW7lL0zdoLRnuYt1vS7mbMHazeDyVe+zG60lb3YxerwhskfYnzGPBjOUN7SPjNjdEf3J2/Mbq9T+m227pPaSOHDXxqd4ec1WT+5XGjDdAx5T5ez3Svux2Pd1L2x9HR88uxrnsrd0WMZ7+/uj/kdnxeGsYqN3u0+/DnbnzeVbk5hiubZlF/Rrser9xt05bSw9WlDou4qcOToa71mJf3YJ+g64+7rTtDL36ALf/67PnVl3enz/4x+uy4n/ru0H/9dPr4kZfr7up/+NIad/rs7vTl86/nbq2P/9fpsxeU3rq1Hnr+9dkLUm+9viZztzKnO91lL8hZorc+G/rAO+FleMIxjyrztao/R54Tfw1t6APDprAGbAZrw+YwGraCrWAb2B62g0NgBzgBdoILYFe4HnaHP8B+8Bc4AHoR7xAYDHvCMrAXLA/7wJowBjaAA2Azcd8JDoIxcm/Pz1rHPCNYKeUQiCx3nL9ijw+GwQBYFgbBcrAUDJf8VoCVYSSsCivBprAy7AWrwTGwBhwHa8EZsB6cCevAJbAuXCHmjr1UMyR9LSR95r1Ut8tZfk/CCPgUrAr3webwAHSEo0m9hVmEs0rCWQP94VoYCB+CQXBjZjiYy7yHzAlNl7a0XNYHWuKuKGwPw2EHWAXeAe+AnWF32AX2hV3hENgNjoDd4SjYA06APWEq7AWnwXvgPXAlTIf3wvtgX/ggHAjXwyFwBxwKd8FYuBsOh0/BEfAFmACPSzgvw1HwNJwIP4ST4JcwCV6AqfAbOBX+CKfBwvbnAAbDlbA0vBeGwVkwXMwriXkVOAc2g/Nge7HvIvbd4EI4CC6G48V+stinwCVwipjPEnM5K1HG/5QlMt18VqLsXavDtdAPPgj94cMwAK6HoXAjLA83wdvgZtgcboEd4EOwm/i7DJcgmsQ7UeK1hzdb4p0r8S6AYXChhH83rAKXwNpwKYyCy2A0vAd2gcthd7gK9oAr4SB4LxwN0+EEsb+c2W4Y50p6pJ+qhrSTdrpDvsd5BAbBx2ApuFvSdw1WgHtgTU2+G4BPSrz7Jd6/S7wHYTI8BJfBI3AjfAFuhSfgU/AVeAK+Bl+Br8NT8E34HnwbfghPw3Pwffgz/BD+Cj+Cv8FPoL0f/BQGwq9gKPwaVoKXYA24HzaCP8GW8GfYAV6FXeE12BM=
*/