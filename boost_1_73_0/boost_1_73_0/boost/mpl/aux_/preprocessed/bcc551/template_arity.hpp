
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/template_arity.hpp" header
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
7PsmBazZbGg9mc3GA8vjy61vFXeIlnMUg1ZMN7yoVBhfzeaQhjqARzeKM0hCtkZE88xCJafQAnQED3h3jo5iU1sJid1NbCWINIZAYMMzcmcGfbyNYC1hBm/omuckaO4/OGNBER+PJxy/kBY719PhH3jv6aM7l2TUa7OtjIy1YhctM2Nnqwozw+4f42lveEW6ECAD4GarvDVTyM8My20YedZRqn06ftN1onBp9nfKOFBmZuwbZ8tKmPPtzwUtJjYbzJkC66bjnBq3BuPmqYFsfDWdO7VGfQ8YfErogCi6LfOjm0HTDEx/eAw42B6UsBHpUJcwXgcfWonkuyRhwXrvMxwAajlHAVTbpQvidsNluELKwCQDutLGh30IAqqw1WF7K6lAmO3uctl8M6EFExHiGfPUNLN2KeOqdG7lmfKXgOyrEesSHWvCB1In1jUiYBMfXWzmJ3BOb3rT2eDq8sQijPEEl585z/YM95A1f+M8sUkU3vEPK+/nx5VLkyQyvIiazr2dpqmNebqxcUMeM+Fxz1RqgfW/cqwjIT++DjxgZNdwmSsGA/Lxp/2t4PmA2D4Lnv8OmLxBXRCywKZinoVpLW8OuLhp3sAIGZB+vjAwfY0/Qi8QA5d0J+9Gt73q6N3g/qMQd2/rgapv67eV
*/