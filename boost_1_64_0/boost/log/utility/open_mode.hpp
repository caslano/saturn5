/*
 *              Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   open_mode.hpp
 * \author Andrey Semashev
 * \date   01.01.2016
 *
 * The header defines resource opening modes.
 */

#ifndef BOOST_LOG_UTILITY_OPEN_MODE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_OPEN_MODE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace open_mode {

//! Create a new resource; fail if exists already
struct create_only_tag {} const create_only = create_only_tag();
//! Opens an existing resource; fail if not exist
struct open_only_tag {} const open_only = open_only_tag();
//! Creates a new resource or opens an existing one
struct open_or_create_tag {} const open_or_create = open_or_create_tag();

} // namespace open_mode

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_OPEN_MODE_HPP_INCLUDED_

/* open_mode.hpp
5N53hj1i1i5qPD4X+QkR8firmDWImkfp5RXzqEG5fx61s7jJK/fPo/7Ive8zQ9VN1Pfmcst7c3kl783llbw3i7xe5HtzeSXvzeWW9+bySt6bLXn0Qrl/W3vb4ubdSvL1gMXNd5Xka8qmiv1APczUjTVubZB7+4HcTf79wKnI/fqB3si9/cBZm/z7gfORe/uBcZv8+4FZIm8b4ebXm/zr+CLk3ny9T+MbLW4rLG7WbvIviy0WN3+qpCw+t5Tft8aNPW6pmyv2a3U3+/dRbZD7lV8LkWdFtKUcMesYNR79kHvLb/Bm/7Z0AXJvHpVu9i+/2RY3t2z2z6PFFjePGTf2uD0n8u4Rbl41buxxe0fkTSPcvCdm6VHb0teVlMVfkXt/H3+/2f/3ce0tFX8fN97i//u4m8izI9z02eJfFsOQe/P1fDFLjxq3YuTe8eLyLf5lcZPIW0a4uUvdRKvjjyH3Gy+WiPyYiDr+jJi1jxr315B7x+EtYlYnatw/seTRl5Xka6L8/uoW4SZjq38db25x017M0qPmUU/kfu8qPZB731VOF7MOUePxS5EfH9mPb/WvezORe9vaHDFLiZpH9yD3trUlW/3b2irkfm1tJXJvW1u71b+tvYPc29Y+qCS9ztsV56JqYubXZx8r8rioca+P3FtW2WLWPfqcGHJvW+yFmd9c1HnI/fJwOHLvb56xmPnNRZUg985FXfH2jzcXFV4/LW/qyBOnHgZRd3dlTmibey5q8tQpZY537dA2X4Q761qhZX7EZncMdi3neKx2pxRbv79tt5tj/fa22LWuR9rOKWO3auu51V2b0rVvY5ZmzKYYszqHzXLMuV3Pupa7XJNaOvLcq+vCi3VduNhdrj5rwpnwJrFbqHp6ou2SfvsZXXu5mzYzR+TX2+oBbv3XhKeJ/C77mrBxb18Tni2yOZR1D3Y31LLVF9z7rwlPF/kYXRPuataEfyvm05164nf0NdG7xF7NiD51kZg1jermMXXjXjN9vBI3qyzhvCBm7d1rwhrvxOhzNpawd4hZhntNuMrp/0bsRe5DSdxecf33oNg7lrJK+K+t/y5sp2NraE8+XAQ/ot303B5uN6UXldjXf80+qsfF7ib8Hsk5hzzTns4W8zZmLP79OzLnYW1PhOfdG2Xm/l8W2d+dmsSwL/n/llPbzFsPEtmZJswWEkaerd0Rhv966zZxm2TacJ7oG6HXdW3RtzJh7xX/2pr12G9E3987B2zsDxT33c09DyPFfh6pOdr4cZ3Y6RB1fXaRyHua9D4jfjQ7fB+E6Osb/+4X/QlO1DlfkdeMGLtHb/cf78eJ/KiI+n2BmDXG1LgpAxHvbxM0v9ztdZKYHR01rEs0LpiRXp0DELN6Ee8Os7f7v0vdJvLkqOH8RuQdI+ax7xKz3hXSlOmKyxVip5uT4JmHWrTd/z18g8iTosZnvcizI9L9uZgdEzlPLGZ1bPlu3vnWiZ0TI+K31bizx6/GO/59ZoLIT4jIrxStm375tUPCPYOQI3+H1RK3R0t77TIt4ITq7max2ypqHLqJm9TI369ilhk1XcOR+9W3kSLvpPmuv2/F7CprHtdWd6M1P9xpKhKzlIg09RSz/lHjd6vI4037XYHeLw/mIfeuezwpZmm+deJq7Yvd8b2jkrx5Cbn3nf1NMcv4t9/ZdeyKGJNa93bkKU1kTIJTYWhMyt/hHpPs68VdNB9Xi937E0Jj0hXOZayIXcs3xOc7ZwSfYn1xqfN63GxndHyZ81n8UOeKhHqmPy3EnXvMumVv1DGL+FQcsy7V8LeI7M0EGbOYC7iIfFtAT7+ROY1/4n8ea8NjA+2cWwNJzkr+3heo72QEmzv9g1nOpcE=
*/