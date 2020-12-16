//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 20010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Based on the unique_threader/unique_joiner design from of Kevlin Henney (n1883)
//
// See http://www.boost.org/libs/chrono for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CHRONO_TYPEOF_CHRONO_HPP
#define BOOST_CHRONO_TYPEOF_CHRONO_HPP

#include <boost/chrono/chrono.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::chrono::duration, (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::chrono::time_point, (typename)(typename))
#if 0
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::system_clock)
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::steady_clock)
#endif
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::high_resolution_clock)

#endif
#endif

/* chrono.hpp
euz7PnFr4RymGqgmTifL1nvegUHLvzF4XPw49djzSbG/6Jil5jt8mgDGxTH0rY4A65EwfINepr8/qg6Ik/prXtd4rWt6QuKq5zTjaJnAcXhqmio4b6I15x5bx3SLevJesK5fzvPulXNcrWL1Makmi/KyShGHT88+Wfx9YIxG3nO+A9PXw+HCV912HPHq4/PEfbp1v5miRSU+zfQCOV5ptGJc0fpamyDvVhk7jOGWfCotzlRKzwF5SvIgxLlL3WicdIRwTQ9v+LNh98y5eE78/SRpSJS8sq/vAXfoxanptsw/NveJ6R6KNrA+tUqhV84JH2xqa53h9YAw809IbND5g29JXncIOn9wnxzv7tEr8VzpDfS5voxwhMm2NOENzPPEBdVFze8leV/1PJyXfLkcxzoGnIfsFvsY1Qhu1v1pypCoDYh/oWbA/7V2KtVRvXYqyeHTTj3by6udGjBQax8cVZ+fGxz252eFw94ebnJUbQ+3OuztIeOX+6Blgn2/DTeIOqDXtuAzmZpVlD/nmRqSXkmf2Ndru72t3Rle9RnVBn4qkgK2tXgQBn12I0yw5xSPBX9O4XjNz6mKpH/9OXWqz/FqnlP6+f5JJN/xzXICP4Nph7w74Mu73Oxyc6ouXrNta2RhQqkv3+i/l54H2qi3zO0JmhdNlDdMd32PREiYNy3562n2mL/030Xs+bA3EP9vW/axycoozaC2TPxTq0idmEv872OavP7t7YEhfppbdWSMx7CtPcN2W4crlHBN9fyQ3mJfhXxuoeeQbozyNzXPIf0ne1cCH1Vxxuftbg6SEEIuQrgC4QinAblRDDcIxYAUEbFJSBaDhCTNwSEWYwVBAYmKioI1Kra0thqrbdGqpUoVq1bs4VGxpS22Um1FixaRav/v2//Ovre7L4RDe/zewOS/M++bed+b672Z+eb77N8oUuY8DxpZr/Y2ECg79i3at5HykfTFmk6Xge1M8Zbk6Ge384e0/uw2aFs8uz1kiPe0zm4Hed3RjntU7P8d4TPAcHGA1+U1i+v8RZhlBnmNTQm1FfJK2o6UqbP37en6eibtGPD71jL+V8v1VAkXavoU3c/vTGm9njfwp+sqlWeFc3W/1m2CY/TCCBmuHSn2eV46y6PRWh6Lqp3KgnTdHMuC11kW9jG0UF9P/5yeF/fi+2En5W16d7Lqyz95/ehnSp4rutyZk/zUycujRZd3O3NyXp4tZnzH9499+JM/db/i1u//9a13//XRcic5LCe5rZOXU4su7+Yk53Xy8mWnIhdm1ZffCET2Mg8fyX3/gN5vrvFwvWBkmN7v1ZRJuArYz6S16AvfzXTdoqTrwHRZinsglnSHW7hfJdNV8X7VOh3nx8ABUdJdw3RrKEO1lukK9NxL5q+SrpcyZUEoI0o9812BM4A9qY+7D2Wu8oCbgQOpl3sQcCswH/gg9cs/Q/3y7wOHAY9TH32GEbieAxwFHAEcDSwEjgH6gSbdMuC5wNXAscC1wPOA64DjgN8HTqCM1GTgO8ApwH8Azwd+BJwKPMbwZ8AZwN4eyOoBJwHnAhcALwE+B/wK8EVgEfB9YAkQ8h4iczYA6Ad+CTjEUv5N+c7lX8vyr2P51zPdev3tId9nks58LV/JdNeBrgtwI3Ak9aHPoj70+dSHXgu8GbgOeAuwEXgrcAvwNuC9THc/8A7gw8Bt1KO/HfhXm950vtPZPxpPUz+56AJjfj3MsFUmh/r1U4BXADsCV/F5EdbpG5m+W5T0i3n/y4HpwCXALIaxD3zCfcQDT0HHeUB/+eemu/w/uaf4eektd9ZZfmb3Fq16yjt7E9VQ+EL4CviN8M3wv4Y/Ap/kw36jz91TdJ3rXOc=
*/