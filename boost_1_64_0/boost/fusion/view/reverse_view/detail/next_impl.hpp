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
7UhtvtRDUWZzba1XUxxaIWZpflAa09z+qYeCzNpleriT6kMzM5uY57iR6ktmdH8ezY/WmdnVlsVnUn+v9NCL2QLDlizCAmhpYqR1sV9qSPPwRg8rWNy2O7dbCrO9xTXIbHiRcFdhHrSKzFr/sZhqCKJlZ/Z7QfkOTHgXbek7vHtNNaDVYjbtRL36NC7JrLztl900D8ms3oDaBam+99H28NLZ0zSeaDyXhgc6y30yWlVmU5duLSvM8SHa0pZeFS/Ml9zOTa4tDD4ma7PYsmHCXMmty3iah0AyS7vox+9pjv4bXd9cTyn5LkS0Dsy+a9suszD4FL3OCk1fUofaTGb5UlX9gWpHK8bs0YHvE6i/ZLZ5xNQw1ZDM+vy8jMYT/oq29XgApP7QeC6jlrcEGjM0vv39M7+nPMYls6L7ZtK2EkpmmdsUu0i1f442pUivL9RfMrvrvjaa+ktm52KnOKk/NF5fj+OX91J/X/AcmtnbS71v0HiiNWLG30kZRvtXkfbifv20wtz/Ru6JR2xJjktxlCdaZWbyHjy2iZbAjL9T1A4G1mb0+ypdaGpxPo24IFo8M/6eS51igIOxX60XGsy/d0pYIKUB4tJLazeu8iVqM5sBOijSVty98VCY12CAeqzNLtUOdRLmtxjouafeaBPv7aQ27TkN8A2zxfU/96e5tRngCEibX7L/TrLcBmjATF/2PNXnzGOA04o0Jc8THeWZzwA1WX8lm9+YQnP7rQFegzTHKPMqGusCBkhk9nBpt3mUC9oIZt7U1ZsI88Rjf8z4+/VDaDmY8ffr6woawMKMnl1Gs6PpmbUpeTCOatcwN9odZuNqHmxF45JgACMz/j5cP1puZnydhdASmPH1aSukbi604sxW/eoYS2ONFs+Mr90QmlouusLqNdjR1OJcaGp5+tDU8gyhqeVpSzTQO6T6oP18xJuV2kSry2xD7onHhUERA9Rglql1nIPyRBvF7NSbXC0pzm6Ai8zGzm84g8alqAHSMXvQ+OkmyhPtp4j1Rev/sRlt02G0iczKfby9l2ooZoCjzBy1tq8kK26A0cxsX5IuC3OUMEAfZseX+1MLC6KtZJa62chF1GZJA8Qq0q7cna5QnqUMMJnFNRtUoBXFlTZAS2a7UyZUoXEpI7d3N9r2eiUvUZ5lDXCb2dlVNeS1TDkD9GBWMXXhL5QLWkZm/HdNdOUN0JzZ3Rwl5e8AoO3hueRZcVGYu4IBGjE7nScH7QtCaM+Yme6eyUn9VTJAR2alegxcKsyLdjdW2k/7C8yn/qoZoBaLO5NndS2aI7RvmLXc+JYMqhugL7Pmlcv+Qf2h6TJ/tX5oO/WN69OYtTRAXr20N5U6VqexHojHgFRfrT/ajj4fy1PtIw2wIbIvH4CWanK3mjR/HjyOgTT+PiQn2r2UX20gvgNlVon4TML8kwzQNdLmILTTM2adJZtqAG9KaT+NPniX7EcD/AbSqlSr/xvZbAOsjthgtM7FHfmEeeYYIIsirfTLLsWEhebicSWlNPM/4XfCAksi+7OIvTpiLSssjJYdWNyJGKrBthSPOcz4O/icaGpxHo04P1ois1G1C4+hXDTibMtwe2f24/dJsyhumUbccgMUZtZr4JxUwlxoanFeNLX6AhpxYY04208a4/mTxnhqxPk14kIacTqfepzDpx7nRhvFrOdvMcOpzRUGKMpMmVjqJ6oPTa1ND1oqZisT5p6iedCIC6B9w+xOp6Q2NA8acbaV6v3Z0dTiXGg9mG3pUqUT9YfWnFnt2o9iKW4V3/6i3/XoRdPx9Zlj42KaWzS1XEJojSM2BO1a8/bbaKxXG2AFs4+dE1dR7WvwXCOGWSXrDLJ1OLeKtFE=
*/