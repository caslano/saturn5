/*
 [auto_generated]
 boost/numeric/odeint/algebra/detail/for_each.hpp

 [begin_description]
 Default for_each implementations.
 [end_description]

 Copyright 2010-2012 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_FOR_EACH_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_FOR_EACH_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {


    template< class Iterator1 , class Operation >
    inline void for_each1( Iterator1 first1 , Iterator1 last1 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ );
    }


    template< class Iterator1 , class Iterator2 , class Operation >
    inline void for_each2( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Operation >
    inline void for_each3( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3, Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Operation >
    inline void for_each4( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3, Iterator4 first4, Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Operation >
    inline void for_each5( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Operation >
    inline void for_each6( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Operation >
    inline void for_each7( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Operation >
    inline void for_each8( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Operation >
    inline void for_each9( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                           Iterator9 first9 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Operation >
    inline void for_each10( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Operation >
    inline void for_each11( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Operation >
    inline void for_each12( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Iterator13 , class Operation >
    inline void for_each13( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Iterator13 first13 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ , *first13++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Iterator13 , class Iterator14 , class Operation >
    inline void for_each14( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Iterator13 first13 ,
                            Iterator14 first14 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ , *first13++ , *first14++ );
    }

    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Iterator13 , class Iterator14 , class Iterator15 , class Operation >
    inline void for_each15( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Iterator13 first13 ,
                            Iterator14 first14 , Iterator15 first15 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ , *first13++ , *first14++ , *first15++ );
    }


} // detail
} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_FOR_EACH_HPP_INCLUDED

/* for_each.hpp
dvwAzo4fKfGJEp8p8YUSX8Hp+8WPj4ITP74PZ/GhEh8r8akSnyvxpRJfw+n3pRzfTKd8P3AWHynxCZymb3D6/cDp96PE10q8TM/jffiUbHy14qniheI1d/SPcw8VTxTPFa8Ulxm4B4rHimeKl4o3cDY+yZ+Re6R4qniheK24mYl7qHiieK54pbjMzD1QPFY8U7yEj83yF/hFZP/MetaO7MPW55itI6ew+tPsHUlY/QO+FJk/lsyB95flH/ATSftrPGcH7eP28YcyF69/BXC6fix8Yza+R4mvFK/hB7HxrXMj/SbxBfwCMv4tnYeXz3M4K9+XSnwNp/kzPz7m5yr1D8UjOOs/SOCs/lzBp2XjS+bryGJsfBOcrc+ZwH22P6ASX8InY+m74v783CM4XZ8bzu5PDmf3p4Gz6zML8PsTwll8DKfrnypeKt7A2f0xC/L7E8LZ/cng7PoKOLs/tRIvC/HrCxSPFc/g7P4UcHZ/aji7P8HC/PoiOLs/qRKfw9n1VYrLItwDOLs/Efwm0r4dLtqRbdj6g3B6fot15FHSvy1hR9Zl60PDh7fs/b/l4sr3A7+sZZ+/Z5bqyDdk/5NwaZ6/RHDa/qTEp0p8rngJP5PVj5bpyNIs/4fT9fXhS7H0e9mO7ML69+Eje/H8bOP7Vu7I3qx/exX037DxXZFSPocfQI5fK/FmVcST8R8F3GflE/j0bfv3la3B688F/DQy/qlYC+U3Vj5dG8+fra8O3554tE5Hfm3b9+8yG3RkzDbZP2ijjoyF5x9YvNkc6SPL37bgHigewdn4vQL+HUs/tlTKj1sp5Uc4i4+U+ESJz5T4Av6biPiW8U/NqI6cJai7WLzcuiPzse9jm45swuZXwT/8a3ygpX7UbNeRiNTP8h3Qv8jWF96R1z99OPu+QjjLH2M4y79T+DUk/4oT/vxSOE3/4bR/QYmvlPhaOT/ZiR/fVzyEb9yD529JP9PdOrJTG++GxbM9kX+w/An+Eitf7I30i4xPCvfpSMr2x4Q/KTh/y/dR74v67+j0edwhvNkf10fmx6QH8Pufw2n+r8TXikvK3YfT56t4rHgKX4jMnzAHofzB9n9VvILT9x9Oxx8e3JHryPgY/xB+/0L4Mqz+DR+beNHvpP4I77bs65f4hynnB6fPD74gK//AR7D6oeLmcO4hnP1+psSXijeK+0dwj+Ds/HIlvlJcjuQeKB7D6fNT4mvFzVHcQzh9fkp8qXijuH809whOn58SXykux3APFI/hM7LygeI1fC4REcv6+P6xPD5WPFe8htPfP075fcVzxWvF/eP5+cVw+vuK14r7GfdY8VzxWnH/BOX64fT3Fa8V909Ufh9Of1/xWnH/JO4xnJ1frsTXivsnc48VzxWv4RuT8k18Cvda8fhU3r9Rwg9g61ef1pG7xrCPn63OQ/tPW8QfNnD/P1h40PzfC3n5JobT/XmU+AxO69eKV/DDyfzM9KKOnDrapx3Cw4s7MnmvyCHDBnzLQddfXIn6e0tkFsv83PJqtD+17PNjgms78gt5PknRkelw/9cZNvT6bP4NaP/qIe2rt3TkMNb+9JeT+X/JrR15eSyRka2hf798QIl/sCNXtXHvLF49gv7ZHvv6aOUTaB8S+/wXeQr1R7Y/L/xsse9PkDzN8/9c8UpxqbgHFU8/EvisJP0rFG/48bG+DvcETn9f8QZOf//Zjuz417s1bOj0R57v0Pl7Gfz7FmzY0Os3mZfQPku+7xLOzl9e5h4qnipewg9l3/8rOH/i/quj5xdYPH6tv33P+n2ZNzqyKE4msNx//+2O7EfGV5Twg0VkDUv7TPJORzZn7wd8R0G8Jf1M30X9X8j8vvfQvsg=
*/