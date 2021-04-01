
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

}}}


/* template_arity.hpp
5ev10d0WswJoNwNMTGESv0yxJh3wabGNv/5do7bkNtEjUpJRxfQggv3Dve4ne5O/CXyq15s2IXFGCM/MUP4GqhMJV5hrfjoouzdklfeGpck78DP7I84uAvbq4c/OQtKcm4IhqU4NeJ6mnpGSUfiTZPFm0JtO03SaPFpu8n9ExsxOmnx1ip3MnOlACgk/JV7hzUNjWVHncCOdULXJ/bmDlM/w4erzox/5xTLLAWJimpYWFR/RzgTyldbVB3LRihbKDidZ9hRvNk68P3coyOY7isOJyQNVDO6uHVkJyjDwweszsV6PuVVnRwGs7J0KsnZ+ASTyk8G/G+w7RgISglkcXNWL0AviJJV0MPeoM0y5QzFgQ9sHsbVsgVrjU45GTXHzjCr0Y9Kx81L0GaYAg0ZzUsVZ0cgmkCustjs50IN/vqW/lKg6xQFclthNdE79vlCA/M8haTuSQ6GxOXFOxBhKaBOOJ5Gv1OdE+MPsos3iIyVLFUIsRrqO7yuVuflzB5HQJ3BEzBw/32rZfd9pJDKrD3eJX89zpeE57gTcB1c/q0WHtnnfFvUAB36TKA==
*/