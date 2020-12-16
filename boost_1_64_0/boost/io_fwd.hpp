/*
Copyright 2002 Daryle Walker

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_IO_FWD_HPP
#define BOOST_IO_FWD_HPP

#include <iosfwd>

namespace boost {
namespace io {

class ios_flags_saver;
class ios_precision_saver;
class ios_width_saver;
class ios_base_all_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_iostate_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_exception_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_tie_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_rdbuf_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_fill_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_locale_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_all_saver;

typedef basic_ios_iostate_saver<char>      ios_iostate_saver;
typedef basic_ios_iostate_saver<wchar_t>   wios_iostate_saver;
typedef basic_ios_exception_saver<char>    ios_exception_saver;
typedef basic_ios_exception_saver<wchar_t> wios_exception_saver;
typedef basic_ios_tie_saver<char>          ios_tie_saver;
typedef basic_ios_tie_saver<wchar_t>       wios_tie_saver;
typedef basic_ios_rdbuf_saver<char>        ios_rdbuf_saver;
typedef basic_ios_rdbuf_saver<wchar_t>     wios_rdbuf_saver;
typedef basic_ios_fill_saver<char>         ios_fill_saver;
typedef basic_ios_fill_saver<wchar_t>      wios_fill_saver;
typedef basic_ios_locale_saver<char>       ios_locale_saver;
typedef basic_ios_locale_saver<wchar_t>    wios_locale_saver;
typedef basic_ios_all_saver<char>          ios_all_saver;
typedef basic_ios_all_saver<wchar_t>       wios_all_saver;

class ios_iword_saver;
class ios_pword_saver;
class ios_all_word_saver;

} /* io */
} /* boost */

#endif

/* io_fwd.hpp
P2+z9EpKy1lq718JC3ftmdY2DW2YrreBrdr6jNGEwnEM2IN9BM8TAMFGC4RbxRdfg6ze6xbT8/hOAib5Dv9tllhMa///Oe6PTs9U3RtDV/QLe0hGmNphC0y4Mk5eviDT5JJorDUaNhr/Vys9VlaYhhq5VdHBmP8suqHuR8W00s30wzskl9ttCCeyIfBmXGDHF/8WV8iJv0I7vhmkatDIy1OI2ieylkN/IeFxnUT5hSmS8FARSGyX2UoBwPjxuXiszjt4bJHORBlRrDNRFmPVBueCkdxOUoAQLr2SF6G5wvQvj+9F7jzUj9ZenusLleTCpLq8UhGHNeGODfiKA9zHNbDEait9BEGaRkp7XlHgzOlz7PbaLqjmkFOJZ47XgWc/GAO2Ibu9SkNze06kAJUSkMWJP/c4ambg7vIw3A/k7AefVliEGp1NxHDtrk4mT58Su7+rx1yCDBhOBw1I1Hptrg0eC8Tzh2dEcIuHuJx9gWeEpg9tuyRo2kg+BT3TOnxCFXM1/agpTaKCfe5pNuwfA0TVHpdQ+5BXUn9HEjGmn+pj+oG2FXswDLnBuVZwu4eyIJN/IDnysWIk3a2CMy+u3DbdqhkDY05NkdQQBxSSypBugzp1wEYHpQK0fgUUHlnjyakUl/CYJZ9tqD4hTfMxNsNjGYvc45H7nVswFe9gbs7yOKo4Nx9xbj5A8dk+EJKW1eSwrfo75sY83u6xRDw53wSWCb4aBr9+giTT6P7WaNyJ9oUn6Uk58i+GDXoyuhrQPv8AiZkZLskiu69AssgqVggW2ZQVOouM6/lMQ4DyWTnUrybrApRp6sRZ5MIqlTEmugWfBIT1dczyArLItF2Q81bkjMC3WKNnYEmmP1Nb9tckc9m/ipRq8hOSqQugDw3PXspl3qxsbDfN3r3KJq6uzVbazpY85Nhoxk1EXMuC2DOQWULf1grKMB9PKDxnuD2uvtxm72zb8NyWxYkQqFPKiJYNHJWC8NrY8OI6T1lUfuZ6HHUyncc2tE7thbQI8UCrDZh0Ti+BghQrpHNzPX0us+OcYr4sA2gVy3xIZiCZTRqWoaxRqlpWe0q71le7q3m1VlGteZw9rmRUN3B4tm1BW5q3CXG4iF9ih2xk15ZD4woNbR6qCzRVCPqjIFfx2OPmp0RImSFaiZsTL/WyaCIHHANR+DELFveIkAPEa3CmFUVeyAim1/LKbA9UWkxnA+xfx381vn/D11xhMZ2EsIN4vv0ti6kz3nviOwTfK/AN4vssvm9XID2+DqQbje9v8PwU0pvMafwkWOhmNu3f9rHCtW1q+w42e8dOndf+/9Pi/nPhj7uv6LY/2ip7C2cvbJLvvpby3T0XH1MePCkm/TVM/82Dx0z/3h1N6SczfdWDxKGtuFCLu1/CRtvcKF2JLNmnwFwDNokRpjST8jFuWeCcDDu4mjNbN63gvwHR/RGtnjTbYLJcQs9EJ4lT78ryhZqpgdPRNsQNIg+ccTCdpcWtUdvJuG6QRkI3yu/Usnz7WxHc5i1h+KULg+5CEHJ4lH3qfPH4MfdQTdYKnPkBWUIY0RvqLhb6ibI5p8uDF/9aWjSflYEGbg30wcb2x2hnsUMeTtAMD9MyNhRVb9HEBHSJ8dXli1hCJvvUJP7SSnltef/+ealRu7B53Furepeo2oV6C6Aiq667uanqfNbMMb1Hs2pf/+gDrXDwZci/l7bo78uHZaWnWljpCL2/425u0d/7hP4jqosRvziu/n63oHl/z9Gqbi+qHqL398OpR+jvvXp/X7y/Ff2l/u2hzv8E/w47NM88/XxKwgiAbC8v9h+KkIWs7pAHhx2P3Sf+U1whL/6G2fHNaF7UMfRtNEru86A=
*/