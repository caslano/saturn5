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
8Bm4Pm2+jFI+F5NCKj1RLS04ZOsxGZ5n4y54nkMjCdF/ZvbAW1qlcehj2+6eFwyQ51nDt+j64Cr9x5uE2YzICc55pifk8oFwMpcy0wfN79jL33DnJEzmnSIjKkKPz56vN0qzW59WYTyNMdHYHCPP6BfrlEHDGzzXQ7f18h14954f2slzG+SFML9nUqSAHOXF/hIt4B/Wili24/zVcfabEiPCG4bdoyYMt+e5HpyG5/01A5jredw3dyPgNU/KxoL8mS7yYfnx1rgfa7hTZQnP62ijiBMJUysyhmOlv6y3hidaL2FsyhInX+4ZJRSyBoXyFKCjsda5fFhL8xcTnZ/9sGYN403CKkTO2Lmb6qJPyad6OhwaeJR8TBnklLi+Tz89aJQ6QHpNd89LlETWpQpP5jPaw/4p+Y1VHhmeeCndfq5n5HYVYKPI8J2zYI1XAY9Za0eILxblUovLevQKw05kfITnQe7yn/twpb/WjhH1FwEvxbke0Ra7xnnm3hpvgf6blQnEXxwDBJjRbOVlPTTyFmW4P971lJOf1WwVeLKlonO4y3P80BTwHNZBF72jIvMt7WH82qTo0xM2Gnm6YKby9bAsxs6YxRr9zE1mGtWi2+Oog8gSac/1SuWgXD8na3vOCzz7IbZwvcLTfqjz5fUUziNevmsnbXh+3iydQ02Lehk5D9DhVOdzvhE0BdYG+7Hp7die49+PirzwgOA0
*/