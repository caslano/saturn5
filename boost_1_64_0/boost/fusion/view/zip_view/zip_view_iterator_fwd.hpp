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
d0hYupCgOL1UYTMxOw//2FA5SgCaa3cvpfcRoRQ6ax8/62yuTLOqOwno/ivMFbSwho3OEXzDX97kHpii4NjeYtUEPYVvs50Sgaj2bnk1Q4qg9T7+qd7Fi0w7NV7Rh4lbnLlzXmwT4btVU9JFGgh79T9L69qYnOedwH1tcczx+JqfSFS6AtcjvtHbs+LfMYYnkEnjKSNqaRdxArHaiyEvBHD9pOOMB0hjU19OQrl1eupS3/NxC1IJLkCVa2mxeNlq4zLAFCQKHpesb/Gwyhcn5TnK+3VGjJikBercMgzLLi3JgXMpkiIoiq16oBuAcm/x5UDWeoJjCDXC3YTe/Eff6bSN0ibvDX6fM2GsmDjy2sD+WwMRDJBF2La8vBvenvhh+MHyU96Korog0WOM9RwZ4jMXnIfN07onQOV90VYcN+4DcWJunO+7ZabwsCPNom6OheRQXGB1tSc+9Egzt8oVTxKtz13mGGdUTU1WOsOUdjm6RcYFRHV4cEFGfhDINp9YVfKnnPjwNjzF2tT2NKQqmKKgQ6mycA2LITLOJGfzykzLDqRVlVz1OFtRig==
*/