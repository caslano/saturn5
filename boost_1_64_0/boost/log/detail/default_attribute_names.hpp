/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   default_attribute_names.hpp
 * \author Andrey Semashev
 * \date   15.01.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_DEFAULT_ATTRIBUTE_NAMES_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_DEFAULT_ATTRIBUTE_NAMES_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

namespace default_attribute_names {

BOOST_LOG_API attribute_name severity();
BOOST_LOG_API attribute_name channel();
BOOST_LOG_API attribute_name message();
BOOST_LOG_API attribute_name line_id();
BOOST_LOG_API attribute_name timestamp();
BOOST_LOG_API attribute_name process_id();
BOOST_LOG_API attribute_name thread_id();

} // namespace default_attribute_names

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_DEFAULT_ATTRIBUTE_NAMES_HPP_INCLUDED_

/* default_attribute_names.hpp
J36NMP3+oNwnOj4jBzfWyDO+sYR7oZiNxOw5eUcvhiWZZpXlRXmLZ5cWLlqY5/WKmaa/FHc2up3S9JfUqbJcUp+SNfa3dvaOp/TBg32Pok5FFdCBvAG+gJ1rY7zq3mjMkkXfVDuiTTPs4Cfk05BZ38H7ux+/09XNNFVfJ6g7Fv10devn+LMTZtPVDDe4F1nLWI99L6IMzN6Hl+r6wz0uuXzHf0bgTfLNmTKmFe9yy1jQ3ZLO2Qyg0CX32yY6jA051C8rzfqlrl019LTuEqt1y4IO6GkdJQG9OD/10ES1b62HJmi9MjlE9bXMT0I/uYn6aQ+H+mmKT/0UPfkmkcbRk++U6C019fCwyq21yqne46Jn+Mt+RlSJToT+JoJ3At+CWzL52uT4rd9mIOZYx13Dc/4m9pZFGPlt1rnevbcS9Jt4i5iHBpUzg/oLd0M+LMz16F9tliGvYQ85s/4wb5rcm9+8rXKfHRTpygxyPKc1R8tvsy43wSyDH5rsMcsPJnzuVe7X3Q71XAf7k0y/7hOzSsc6L/ac67z6zbpNzF+JMOrlN8j9Y7hxpWs9b+YhSzk6UeLAcb0+z2m67rucZ90tMr+PMMqoX8h9P3drdlUz9nf7o8TF3OAFrKz4J/sH9XL3CrK/A+c4d6g/4ye/9WezXDskMpdEGOP9y6Z67jcx732OOe69U2RSItq4Two3yuv94s9xWrZiel5D+ZFo+u2X4jeHejl+c1xjb6aJT8R+DvHyCWODnZ3q3bjRZN1e8l6dyPzWjPObJQ5nB8W5hgUlaLxuFr1Z4Ymu04JmBh0Mcah/86yj1/G3eMp5kXvAfN4jGndtXdERDnVt3PVfr9+Ke6+I+W2me8/JfVpEe1e45mlqGrm6Dt2h3oz7znV5rUPtF/NV5vdhD/dIm3nr2yme+1HmvhUfyHu+nPHR8Y7pMEHff4joTQsOYSXDE5oGUi1+4zd+c6jT63NGy3OWOKanWPxeh98HSBocFL4tLMhlrdsbefl+8fu9QamuKFonbYKmBY1XM7em3x5h7VwxwX2D73G9FZwZ5Fu376Xp/01JH1eF93O97o4Kyg+qCCl1fRRyibsgbIPrpPAgM65uFjeH6736ma9frNZd3hZ3rguPx461vp+g9odL3usZNITVIe+6+zrFr4R9PW7tk2f9JKy9hl3bB/KsWswTxPy88Lcwt7YRemk+jxW/vBve1cU4JOp017LQraEdXe3C/unqG/5r4gk585v32/Aw1yWh14e+5bomrKvbaHMmYMYzIvy1I4Jyve2IWO1fmCB+6hL+K/zk1E5YgcwRSROLIhzaCeLmh2LeXeKmvSedyDse6uqh7Zt1uBEi/poXYW0z4Acpn7M9fiCEncJqHfcguErewUm41l716LURvW7oBNnbDmpnLm7iJ7NuXi3hnmna/6mY/zm4lWtHsMhY04a2US8UGXf4jzVufpQocUNCbOivaiPhuiDCt41ilB2vExf4NjSGQeIlQbcGdQ4NdSVouL3Pe4g0tNY9OMgajjIzHDPFD63NcMyXcCSbefJJyZO9uLeEC5f85flYbW/miVxU+BrCpt9qLvlWsydGwzd/c47k+YjWnpkf7vzwJNv3+Qa+z/3CZ4Unu1aGB5t9N4fFTnmExFkHe7vqcYf2U2cNW6T4KS/sdeo8Q0IiXA+ERLr6hYW6fN+PrX2l8XCRpIcnnb9Nhjz+kITLZdS1hsr7ecOd6nqKdcUvm/n+PAlfu/Bs96vBBaGRZh3rIpFv7/AdyAgy+pTyxW7rCKe2XWf1b723jhdxyD3OfWXwz9wXhMa7tvMcf9/WGp/vS1vbO2toQ/1O3L0zwqld95nEUYQZZ+mSdhL8PnM=
*/