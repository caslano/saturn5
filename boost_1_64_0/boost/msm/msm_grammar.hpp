// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_GRAMMAR_H
#define BOOST_MSM_GRAMMAR_H

#include <boost/proto/core.hpp>
#include <boost/msm/common.hpp>


namespace boost { namespace msm
{
// base grammar for all of msm's proto-based grammars
struct basic_grammar : proto::_
{};

// Forward-declare an expression wrapper
template<typename Expr>
struct msm_terminal;

struct msm_domain
    : proto::domain< proto::generator<msm_terminal>, basic_grammar >
{};

template<typename Expr>
struct msm_terminal
    : proto::extends<Expr, msm_terminal<Expr>, msm_domain>
{
    typedef
        proto::extends<Expr, msm_terminal<Expr>, msm_domain>
        base_type;
    // Needs a constructor
    msm_terminal(Expr const &e = Expr())
        : base_type(e)
    {}
};

// grammar forbidding address of for terminals
struct terminal_grammar : proto::not_<proto::address_of<proto::_> >
{};

// Forward-declare an expression wrapper
template<typename Expr>
struct euml_terminal;

struct sm_domain
    : proto::domain< proto::generator<euml_terminal>, terminal_grammar, boost::msm::msm_domain >
{};

struct state_grammar : 
    proto::and_<
        proto::not_<proto::address_of<proto::_> >,
        proto::not_<proto::shift_right<proto::_,proto::_> >,
        proto::not_<proto::shift_left<proto::_,proto::_> >,
        proto::not_<proto::bitwise_and<proto::_,proto::_> >
    >
{};
struct state_domain
    : proto::domain< proto::generator<euml_terminal>, boost::msm::state_grammar,boost::msm::sm_domain >
{};

template<typename Expr>
struct euml_terminal
    : proto::extends<Expr, euml_terminal<Expr>, boost::msm::sm_domain>
{
    typedef
        proto::extends<Expr, euml_terminal<Expr>, boost::msm::sm_domain>
        base_type;
    // Needs a constructor
    euml_terminal(Expr const &e = Expr())
        : base_type(e)
    {}
    // Unhide Proto's overloaded assignment operator
    using base_type::operator=;
};

} } // boost::msm
#endif //BOOST_MSM_GRAMMAR_H


/* msm_grammar.hpp
XfJ52jy5pE3musoe+XKSedzz2OEROW47ru/Uf6uvP2dO+pJ9hPk/4xi1bq6ovkVZpxtr6l7vlQe+lxUeFif3eI65L1rJ95NidXF63TptMC7L+vIecbrEa+aO7qPXGBfm9jeaa18klvea629xrEXygu3mWPV6ruONQ+T7lx17G5/Z6/WJ+JeW7aPOsx85Ur5M29a02NzmOGFCv/7Csdud6v4yc/Al5pkXyZVN8nuT+o44X5Ozuc8ag1dRle9t5pmXmgcetT97XO7YN1RHjJfd6jEZdx8YMXruxpD8m3nnBPWTr+kjtPm4daF7nzGcksOnKd+yfR9Qx+Yxjuexj210DwfHZZbJXKifvqBfjZvKWzf7PNRx5jH2i780d3xH/unnvnfYl3zdPF+2z/yH++XtFeu75Jf5trtth+tTjgHmHFNeaDzcJz6/EsfLzH/2Hck7vHd21PmX3NjqeFaOJcWu8qnmd59ts0M/Hu349iPyMm4u+pi5Mi+utlmteO0w89U5+se5XPdf5O9DwXmQ58Z18t3q7Z6QXWeZM5QVe9xc+wJtqze/gxIz96qrPOveIibnm0ONw8p4NPT9abPcN0btDzJv3BxyXcZh2wbnmY7l7Fer1zo/WvT4HGPmBXLEMWz3RuVZpmyfHnabk99krBrDheduMpb1+yv0t31c13u16dYW4yuErr32i48fLAbq8RT59GrtXLslVMUx+xdxpWy/UrVuOEeZF+u/S+XDi20zrj99vuozT3W1j7rNGNwgH5vnKa7pVeRi/a324zdoz5TxtCRHbjV2790S0jfbtzkHSt9objvduL1TDtwr71uM78eM9a/IxacaF3vNa9+R68Z09+dt4wPOwewv683nzmEqB8ufq8T9586TbjaGjc/sCY5h5HT6BvU6wu+ffkj/nieut4v5g+aKkhwSq4zlk9SdP6WPNxaz1n/BJv0gf80v1ZqxIX9yrllUv668VfuWm6L+D0a8d5rvPy93YmK1xTz3VrnTKd4l51OW6X6GsWoeST8kRkU5OClHvm6ufZrjxjcYO3duEBPXSlrF6AR1/pvXLrZfyxijjgUqYpn9TPNY0nzSI2e+GfXdYuPiXMfsZxiT39OflxovJcv+1ly/IhZBDJrrnWucnil3+y1nzgiHandRO91Pu2C9mOOs7Mn61DKFMz13r7k+r2XIHRYLGc/Tl0W1y7xi/awYxU5NOMY1XnudgzU/6ypsMD6MywO8Pi4H/mkZbU0/Ie7XyKPTXfep+e7p0+3nP+j5OseMb5B/77Aff6CZLwn3JpNDPo/Lya3qezeb99XVXOqeq75/ZVz3xvwWhfe/qG9+gfeDuTe4H3T5Xc05Xm5/wrjqNjY+qR6XiGXe39Ni0ryG8A/b+bHx3qz/oa6HvEPdbtVe8U1eG5fr9ufmw+RJ2umaV3lR/zwclT/qe5r5sehYU/v7XmdcTVnuC+azNzl/lE/J3fL4Ju/dYU5yLSuXF9/DLH+12N+qP9W9tE+83Lcypsz68dpxvFx/pvwyBrq/b7z9Xpm7WnzXVozj4tUlrzY6l5dHFeMv8xp1rfs/28fV56nyyLWeMC/flVVy/FD4vPzqsq0fa9+X1OVB+fp8x5DGa8GY6T5SXJXXdZy6HqkfnO+lzcHlGfFxbatg+S7nq0Hfxu4Mods5QlZMsuPWlRvJq8y9vouW9H3MzGn2gZbP2AeXCtoxJHeOiLguKId9lzJrX1WQP123yfN6cGxlzvMd+/Cj4Fw25tyweUx7kHnWfLLN+PuZtpvr0o7Duy9U7qBcGfb3ZNxcK1bKCj9z3K/N4VLxfid3Or69wbIFx5TyN9siV64VC/2Svs94+4JlxKyy6HXHZfU=
*/