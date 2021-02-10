//  Boost string_algo library string_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_ROPE_TRAITS_HPP
#define BOOST_STRING_STD_ROPE_TRAITS_HPP

#include <boost/algorithm/string/yes_no_type.hpp>
#include <rope>
#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {

//  SGI's std::rope<> traits  -----------------------------------------------//

    
    // native replace trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_native_replace< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };

    // stable iterators trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_stable_iterators< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };

    // const time insert trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_const_time_insert< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };

    // const time erase trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_const_time_erase< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };


    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_ROPE_TRAITS_HPP

/* rope_traits.hpp
Abwyl25/iPceezdsEcoyyLs3FINAsddij90XK52Lpy/zy1+w/8kfhHUtG6eoCKgKPOPl9Vk01RmN28EAlfWeZ57m+eSx2cHY1vqa0LlB1LYOFGYSpGQozrJ20AlCfVvhcmdzysQkBaFdsoi3J/0xp7V3p6iHJkX/m6Cfr++H4pJHo0xc6E9iXamARcuNFyxZVqtc2i0cOZQgUhAv+it7bsgZSS+cGaMLcXE797gGbDkOK+LqMvRbJQ22YBAIph0Y8TMXmp8CAgV7byrFwYQLa4l8yX/XXe7s/jqcfTQJQNOcCO8Yyu3cyLuuM5CeXO89FbftBas9UJeozSGyzj8nzxTk38HSgtWujoDKLvGk2PDsQZr5JGZSrNHYDxC183MVoONHFtDYlO1ewQlkICDk7HhaOKhdnn79xHxfD10H4tecHa/DI/1oiB6N6oaCAinRTLPgfDO+cXfqBHDMk5TBzLNF86gLHtffNwb2ibh23J6Udt0QTNK7DTllZ3zUYC6pC8fUql8QPZ8hQM7JtMoTH6+4PsnhD1GbiHloqSDL/TiqhwXvGHLCzds7RglGVeRRuoY+2qgNap6Ins7RjH/5x+XD/Pru1hPGcNyfc1BGrp0qqBkG/HwCTyEZu1WaVwhllOGushcrrZ/jZ6KS
*/