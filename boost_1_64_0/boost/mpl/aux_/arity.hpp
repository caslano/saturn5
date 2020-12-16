
#ifndef BOOST_MPL_AUX_ARITY_HPP_INCLUDED
#define BOOST_MPL_AUX_ARITY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/dtp.hpp>

#if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)

#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl { namespace aux {

// agurt, 15/mar/02: it's possible to implement the template so that it will 
// "just work" and do not require any specialization, but not on the compilers
// that require the arity workaround in the first place
template< typename F, BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct arity
{
    BOOST_STATIC_CONSTANT(int, value = N);
};

}}}

#endif // BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif // BOOST_MPL_AUX_ARITY_HPP_INCLUDED

/* arity.hpp
I2LahzMpX5TM6EHtCBe2h3rxwL/HMdr+PeZ4nxX55vaSeOMdAP7n8Mj36k7be1U6Y6d3zDaclm3OYH74RhWLElYSguAwr2upTgCkIJBhI7uy5Zv70uRXYqDvadpjGwWwDvehJphlhPPIjZwU2chaNOJ7c08aPWOlr88t5WVbAMgWZ3BE+NqAKKBYdCDW/+JTbcA7RIjzKl3Uivw6ilwSNu3xpngV9dJBNQEpt7AisoV+BCfRQhR7m4qiBAjG4MdyVTeXl212BJvSi5JV0Hf2yN/B1ET26f9SakKsd8dz9f4fHGs//FiC/T823n6Yjf1/mn0/QKwyrJN8Ki8GC29vT/zclL9QsQsXgl24EF2fzrl0pQzMX5hVdRfunYXMHtzUU96IcyvzF9KDi1mCz6vU2ZUli8cwifwaVZg7xlyULVcjSLLTxZS+RVKlsyk+kcoDr5PDMy3GVqoSErgPd0gKe3o2p2/hBX5FpU8T1S7T1Q6iZ/MBlV0qskdyNsQ4C8RIFwhmHP0tW+Ao7VyZvyBr7ej0gxWFMyjnzpGtD/Z0VhYumDsyk8TvM4Tg/TcYkdo1Q1XboZs4fQtGWnVvKYn1yJDsOPuA3hP7f47IKdLzd2IPiIztk7fiJEweZmvLWVhZzM4G/k5VAfzC6nOJyVZdTH9YXxLVmMu4gMaBxtA+VmJeedk8R3BkZcm88kHO0GCe+1U0S0to7ueR36Q29ivvOJ7BVTSiJaRlt11NsMW95yORPuxfeiSO6CPOS2VPHf9mYKzzdHVPxL8pShgfdivxfyNszEfkYBGVX+BcukzAYW0LXQG3mHCpYQiDHzGJ5zPhIXS2WnEphJGSjPs8XVoYyT84FL4JuAZMsyxnlS05lbRdjyBycuP4t4MajW/W8bbxQQc1GzqoVYL/XNLBrvTQna5AliL16hbtU4SK/5O9a4GzsUzjc86cMYcZ5gwHg8GsSykpoVJUcksyNS5T2hBRfU7RxUyIIU1iTIMtShshQypahCSEbFS0blt2m0plZ7/TmbbZbdqmVmaf9/+87/t9Z+ZcZsJuezm/33DO9733y/M+73P5Pz/0q672Usv7h1duz99+gSoVMZvQVJnbasOx62CTIS3ECoTQ/sIW9vV9nsb/fuzcKs0UyQdXu5lV27v28jD2/uR/31bbpl9LM8fKsSfPsTv/8Ho5lxHknaxv5+cQup4TZG5za2ApJNAoPIHLwRC1xHd2Ye3SR16j4Z6PZrUwxmuZyDaSIJt/ryev4GWnE4I7jP1fVxkPp4+0X70S1oZQTnQCQ7IVoVt2x+RfpwJ54rGKgITHLkcCcRonq2+PaMX/6irtw/qnKAgQNKcv/EJ6wLfkCqzsLgR73C395NQLYDypAoY5slNZS+bF7YAdepLtyyk2amPs+6vgMpt/4IAwK2VHa71SztUrZWybyislxvJceDPyYkX9k3D/vczOD6AlUgfZKBaKBdWejWjPRsbCam0xARtz+pI1CTfpg9aySfNJ9Ed3aN6hO9XTBQV9FtAGnD/QHMdqdXkMrxHWO0t0XVQcGI6NKHN3K9n3jUkF0yghlczFjlXFFub3KaRI7xXFHOX4/kZyYrfk5hQKj9b0QtBOUVNP2HEUymvi4tycxeA3FzuyXDRojwVEmhY6DZSKq/MzV5M9KfdYWXHCq2+dGpp1GJp1+emryRnVNjTrkgp6QES4joZndYb5ArcYjNY6MTwo+lfq6eOk/hGcBJgZcSabDyZZ/FH6Fnq+TUr/HicUXPUOLRqLerZIZmQ/cV3vyWM6pyM/L+Lnz+A5+CZ+vo0lljPwXPFNTbk4cENrRBfXUIegS1kTM7UNCRCTNg+pW5KXOZvezCEW6WE=
*/