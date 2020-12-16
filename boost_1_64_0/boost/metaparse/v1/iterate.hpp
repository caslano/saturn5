#ifndef BOOST_METAPARSE_V1_ITERATE_HPP
#define BOOST_METAPARSE_V1_ITERATE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/iterate_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class N>
      struct iterate : iterate_c<P, N::type::value> {};
    }
  }
}

#endif


/* iterate.hpp
F50hrn8rwlhulcghD1mLmaLHGeDz/m0yyNi/I/a8LzGOE06SyLGILd4qksglpzWN68KrJXLbJ7A3x8D+ryCk//3x+N4YLs7Dv7Dnm+A3DT9EIvNHiGcProIvvxu27wLY1HsJebYj/NxrjPhabGy+b2Mxfu+ECMlbaY02w8EiDVcxmJ/OE7BH92O/5yzl8UOXDKJAtr+Gf3HCy5D5m5rG+SbGOS5++zO+3Ka3IL8How3L4EcdC/8qh5AfIHOjNnD56wXZRCz1WHeB77AhPBY/mv1ORVxWVIcx6CORL0qM+NuClk7Q0lOZmCZ/L9PR73f4z7ox7PaSeHbmFXGgIga7nvvIlxNyQUjcvwU2eTXauOYk6OZerP3H9k/cjknPGe936MOuu25tfuxO7w//ATw41Ald8kNi3I++Q8gsxI/9zoT+UUAv0Lzb9fAT4OPf+A781iMlchniv5e4H9NjezyOpdBXgyA792+XyN8RF/kgO5ngt2ffl0gO5Ln/4zBlyMlMAa621Me4UCJXIhYJInZ+FGXnoY1D6DWefbQFfpqEseoEnwT9+/RFUc9n4431bhll7NNQ8NB1fxjvfQGbVA7d7EJeSIZfWtI+Of/7uP784cimyxy+Df73Etjkk2N4apHx+ucV4NdV8KWWcH6Av9HhLnaecTZvy3fQE9DPbRDr1d8OmquIm1eCbk/Bn3gLuhY+9eUPSOSYm2EPkLP4BXRNdOz5Bn3MI6Q1p8GsF3isPJiQOTLoAP9x42vwhxGLTOB26o9HEuO68TP41R1j/Ka7MYZ14BP48ce8Cb98EcYqqLOj8LXu74W8H88D7JDhe2LMvxsAfxI5LRf8mDu3IHZuQl7OPwptnpm4PUtPgfyA5vpjwrYmxu/MxDheeL35cd/L5fBUjMXbsP3/gH/2Qjv27PMzYMfhix5xLGz7E8jLZGJMPcZ63usJn6t7E7IIu+iezuMS2JCByxnsJ9xHGC4ZcXlekcgW1Nfzpqb5tUxlz9oVS2RsBjsvXwPbBP5d8BB0NOi5DPoyAn/zGtiPzsfDlnxGyKUtJTICfu1P8Dfz7o7H25ALnoE9zy5g19ljJTJZ5xfvRH2tPweux1mdbWEvP2zfNF2lBeCzLomfPTRInL/TL7F/diLyQ6e8jtj5H9AP8PGWVRhpkvVo0zRqlcDPbRFGLgpxZdV8QvqeQEju1ex+n9XxeF663ni9Q4ov89gXiLMRSyz2s2drkA/8cyp8BcjPFuqbxcZ9J6PMLM7D0AvXEomUIR4Igf9ub8n9yTsZrsitAi73e+iSkdCh+KNHrU7/3fUHIcdAdzqykZ+6UMCEdTTtTGPobuDdG5um14fw1664Gf73DND7McTNb4NHdiMnDJ7deiH0+0XwI+6G/oDOXlqP/sHPORc0/BF5oqoO4CnE9a+C1z6ehbjnNR3PcFt15anInT9ITB1nHwlcyIXM2wKYa+Hv5cEWwu6WIhc1cB/rw0d56HN3yMkm2NSnm9ftJccght5gLHPdnZAH2K56yMYTEcScg+ErOGH/6vGL/EzoXdihdvG47sjFXMk9DNeNoMfbnxnxZoIXsnheaMk8ieRx+1uxGTlE0FB6NnFbt8bI40Hgt2rY1VcugD3CeJwBvfHIZOS5KsE7d0nkpO8g1yuJpWP54ag/D+OHtjzRIZ4/CzbCNl0DXc/jrUGwm+/kIwb4FuOBOLXX6fArRmN+ZBrG4xfkIrLBuxuR9/kCNh8++CrQeGUVYp03WB9PQF57yDDkZuDHzoE87YHtiXwJ2O8wHt8jBkSs1R1xx8OY58mHbXmd8NxZjM8yEGO1s69ECpEHlbnMf/AQeP8r8FUn6D7Ir/Ny5Cb3Qd8iRvk=
*/