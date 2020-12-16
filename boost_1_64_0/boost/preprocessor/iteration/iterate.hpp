# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ITERATION_ITERATE_HPP
# define BOOST_PREPROCESSOR_ITERATION_ITERATE_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/slot/slot.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ITERATION_DEPTH */
#
# define BOOST_PP_ITERATION_DEPTH() 0
#
# /* BOOST_PP_ITERATION */
#
# define BOOST_PP_ITERATION() BOOST_PP_CAT(BOOST_PP_ITERATION_, BOOST_PP_ITERATION_DEPTH())
#
# /* BOOST_PP_ITERATION_START && BOOST_PP_ITERATION_FINISH */
#
# define BOOST_PP_ITERATION_START() BOOST_PP_CAT(BOOST_PP_ITERATION_START_, BOOST_PP_ITERATION_DEPTH())
# define BOOST_PP_ITERATION_FINISH() BOOST_PP_CAT(BOOST_PP_ITERATION_FINISH_, BOOST_PP_ITERATION_DEPTH())
#
# /* BOOST_PP_ITERATION_FLAGS */
#
# define BOOST_PP_ITERATION_FLAGS() (BOOST_PP_CAT(BOOST_PP_ITERATION_FLAGS_, BOOST_PP_ITERATION_DEPTH())())
#
# /* BOOST_PP_FRAME_ITERATION */
#
# define BOOST_PP_FRAME_ITERATION(i) BOOST_PP_CAT(BOOST_PP_ITERATION_, i)
#
# /* BOOST_PP_FRAME_START && BOOST_PP_FRAME_FINISH */
#
# define BOOST_PP_FRAME_START(i) BOOST_PP_CAT(BOOST_PP_ITERATION_START_, i)
# define BOOST_PP_FRAME_FINISH(i) BOOST_PP_CAT(BOOST_PP_ITERATION_FINISH_, i)
#
# /* BOOST_PP_FRAME_FLAGS */
#
# define BOOST_PP_FRAME_FLAGS(i) (BOOST_PP_CAT(BOOST_PP_ITERATION_FLAGS_, i)())
#
# /* BOOST_PP_RELATIVE_ITERATION */
#
# define BOOST_PP_RELATIVE_ITERATION(i) BOOST_PP_CAT(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_)
#
# define BOOST_PP_RELATIVE_0(m) BOOST_PP_CAT(m, BOOST_PP_ITERATION_DEPTH())
# define BOOST_PP_RELATIVE_1(m) BOOST_PP_CAT(m, BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH()))
# define BOOST_PP_RELATIVE_2(m) BOOST_PP_CAT(m, BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH())))
# define BOOST_PP_RELATIVE_3(m) BOOST_PP_CAT(m, BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH()))))
# define BOOST_PP_RELATIVE_4(m) BOOST_PP_CAT(m, BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH())))))
#
# /* BOOST_PP_RELATIVE_START && BOOST_PP_RELATIVE_FINISH */
#
# define BOOST_PP_RELATIVE_START(i) BOOST_PP_CAT(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_START_)
# define BOOST_PP_RELATIVE_FINISH(i) BOOST_PP_CAT(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_FINISH_)
#
# /* BOOST_PP_RELATIVE_FLAGS */
#
# define BOOST_PP_RELATIVE_FLAGS(i) (BOOST_PP_CAT(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_FLAGS_)())
#
# /* BOOST_PP_ITERATE */
#
# define BOOST_PP_ITERATE() BOOST_PP_CAT(BOOST_PP_ITERATE_, BOOST_PP_INC(BOOST_PP_ITERATION_DEPTH()))
#
# define BOOST_PP_ITERATE_1 <boost/preprocessor/iteration/detail/iter/forward1.hpp>
# define BOOST_PP_ITERATE_2 <boost/preprocessor/iteration/detail/iter/forward2.hpp>
# define BOOST_PP_ITERATE_3 <boost/preprocessor/iteration/detail/iter/forward3.hpp>
# define BOOST_PP_ITERATE_4 <boost/preprocessor/iteration/detail/iter/forward4.hpp>
# define BOOST_PP_ITERATE_5 <boost/preprocessor/iteration/detail/iter/forward5.hpp>
#
# endif

/* iterate.hpp
jBCYAQJGCRAwKkrEKCkGCDXBEKKldmDIDFVEVLTPiBZlhsUiiyFCGIKoqFipoqKioqIihNVg2ARUUFQUNyrqnT5RrMoiy/Q/59z33gRtv7bzfWfeXc/dt3PPObetlZu2bW1lSzIbxcuJ5JZR/wTMZgfhbw9Qwkfb6EzN5oSQzTt0islxXrWxjU7dNdJO/Wova3Jty8EhAyFBzDDnJFasvoSD5KKujaNQNY/QjSMvI9vB1ZZxPc8ossy2xm6nkH/1Om9OaKcZ4qT3qQ6bYyp9Se+fQtQDSX7DRS472ojEgxdiJWmiUzcEjU6vpNnyRm+IhCHEjdQTcIV8yriAmujTr1a2i0HIZooujZf65GJvNGzkO7m9LE14jPtVHz49dvNBhPDi4dAiJ8A5hLU8K17CDJnXHedFo1KkXroDM/NFE2bU1UCaXQiClfQfpj81krf5OUbJ3RDzwRjrozIlzdBA9Q8PFwSExtl9MVas5cG4nV9D3QdforIirNb/+45HcvvpyfXnY/1X2HLIa3bhSCWqabbHrqa9Ht665uv9dQT7XY+MnLGt0ZIkLaLOgym9CtmgLno43T/jeo/oJ59ayg+VtDWCTrW08VjvoPhrbvOIuJExnPyjNGT+Qtr81A8BSePFQOoLIdOrEN4YjbBh9TB8RC7bizEzQCgzxbbi6iBXo3qupTxeCAb0pc14gNGj3Zyp841JTqbucFOvrA54EJtlbYLqI78en8/wU005nOH17l9keKufky4kgIa8gHSZbBqGq1l3nunnyrTK8De3XYYPxCfIjFt3+ilwvaRaYhdkqMZdpj7LZK9ilGUfz1EFfKMtFTzXKctLLl3BHn9Na0rsbyyBPclvCbykH2wMmGl4NMVf8z287LJwNo62osDXcOBAv0d4DtzGCEJ+PRqoaJ+TE7PUXrEI+jb5ULmoGXcIIGnlkcahIR6WDC5yMhiQDDZNt7oVn2mtmgw5Vbq3lV1LhWrQcW4MfuftavM3Rr2DdmXSTf0CoYPaJYbZI3U2eRAhELlyoHoOJj18zgXGlEdDfI1h1VNShGvPBna6Ye7OO0DjmQx605RS1/lTBd6FOcRKYw+qPhlygoudHhHRivPJYRCrWiAFdLWnXdlYxaUVhb3tMyzVqm9H1EMtOb0IiCmdVVAsEMtWZrNf4FB16XYr1MvW7ADeQfhlQEsegxWE4u2w5OQ8eaEHoxwHB9xGGNNH0jH1zhNuVzm9JXpokvrl+5H1CwKkp6pd6n57foClNxtED5ko31wKN8jL4as1+PBnutbXtZBob0YS93IzRREBeGifFw0B9GS+1ho4ib7qQtAemoSv93H4lT4Or9rAnxWiDaPg9S44k/w6kglif98A8yitjiyqtSpREISfcD8lI1Ly9wIoZbd8K9yirWyuiP4VA/IBwwEjAWVavByfZfKpl4IZjqKyJU0UnS21tJuJQuRuakkaPcaycgC2Jbp61D2fUlfO0wrJlOdzOUlM8bCAzDn+GYbMorvqICa8jTUQJyrhRGrh6NyZqNCWqWSBZAVCeTjU+Wz2sfkMNgfYfCqb09jcgs1eNifdovuMBaT/KZZubPnS7UjVJXaLZeS9ZNkmlhIOtk7kGY2gOvYl6VD46n37dvcJeGltJqnnhcxjbto457MUfiKQIR2Akd0qmIuo2RKjtIV9IvjHvStVaoLuu9UtSMfSedVHQhqc1fPINwhf2W+qjS1svTx/xjqVaEn+BewvbWbuUV1gZSViB2BXbcU2JvF3sqXDZimm2kkOP74HB4maaHBJ/+I8vsL0M/hSv088KcI6ARK5U/2PoswHatkKgo4PAZ9HQCxffeBjTlSPSrRi81Y1T4yjzBtUrRg=
*/