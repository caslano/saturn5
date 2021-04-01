/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07202005_0856)
#define FUSION_NEXT_IMPL_07202005_0856

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <>
        struct next_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename prior_impl<typename first_type::fusion_tag>::
                    template apply<first_type>
                wrapped;
    
                typedef reverse_view_iterator<typename wrapped::type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(wrapped::call(i.first));
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
RSm8UkmivETmZqfZY4k6JMx/gsJnT1Dd2xIhxQUudTUZqxbZwj0btb6My0GD7fJrD3XAunSApiALuz/OSd7ocSD0HP0BfwXTWT/drIjBs7xhm7kc4IfIfvuzWP+dve1lxA6dDZRVEFZyn/89rb2ZmsgV9LBqlhXxqagYZbrpU55ia5rTq/d1lfYrNYRpkCWyO4E3QpMt0fOBv8aYvIhTeYLbLgY1FlrQVhE4gz5j8zTb4nGvP8Rb4zkSaVQn69XPbqNNPnhtlTbzh7lVqnUm0PinEms66kzD6xcFdpBLduQAFIs8fKFjjMtrfpYymdMW/PJoIFgOy3pN3LVoCCHRF5blxDbK5s1h1iD+U1rE4oqY99IYpDgGcvbAeqexhu1ERNtPES6c5TBYmesQmbf10TBi5Ig9cx7eDLyJU/SO67ykFuNpxG30Qncg6hupJoekrKkq3dv0PdfvcbK4MzNgmis/eZFffDZlnErePEtJatzuvAFvOSkIJ3MKxzPqvIzJLePuUgs0KPEZKWLqsFK6OyTrwH12Be0NueU5UuS6lS1NZ18tQqQ//wJm6Q==
*/