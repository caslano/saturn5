/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ZIP_VIEW_ITERATOR_FWD)
#define FUSION_ZIP_VIEW_ITERATOR_FWD

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/detail/strictest_traversal.hpp>

namespace boost { namespace fusion {

    template<
        typename IteratorSequence, 
        typename Traversal = typename detail::strictest_traversal<IteratorSequence>::type>
    struct zip_view_iterator;

}}

#endif

/* zip_view_iterator_fwd.hpp
KtNI5naz1bxi4W1qDXyvazbyRqRTCEMHwymNpwc0E0aZHv04vn55+fqafhxOJsOL6zd0eU7DizdM7LvxxRlcr8AsJ3mb5dKAeU5qmSVKRp7nn/cZtFqfqTRMykjSAXsvMLIos3580GoN/iQerNdlmqxpDkWyRCBIx1c3T2hWqiQyf5Y6Aygyj+ScTl9PXk1G02B89cMTGnSbHEMNNUO9VOmCyoyc9vbQy+EPo+BidD3GVzC+CF5uzPJ1KguFr4FK+/E3rc9kijDdPXf2YvdINLtn93ByNQwsn+YJkWdiwGzungqCH76fNrZ6ORq/b53aYnY1uTwdTadbrLJchwir7SNVDCAEIlEIDoDNosG2+fZSrE2hsp01YeKdgzFyYmepyGWe63x7lXEDC4OuRZtEmIJOqH7M6WYq6JpJB3OKE4Oz1Lp+K4azXKXFjsD2wVIudb7efoC1SM7KhY95C9y8V2U3IlFRu0NhLMO3BvgBpOPoQmghwC5fwb5dgOivpcrlUqYFUIa3LBnzHt1IpjSTMgVcFRaScqRWDiy6nrwekbKIsraAevkdJ/agNdM62WYOa5Uoi3ZNCrOmLnunR3491GmKsslr1OVfOq3fWkTtG62iDq8+w29q3uZHh9+oLLgBHALU6fnzXU1+eNpp
*/