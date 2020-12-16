/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_SUCC_PRED_HPP_JOFA_080913
#define BOOST_ICL_TYPE_TRAITS_SUCC_PRED_HPP_JOFA_080913

#include <boost/icl/type_traits/is_increasing.hpp>

namespace boost{ namespace icl
{
template <class IncrementableT>
inline static IncrementableT succ(IncrementableT x) { return ++x; }

template <class DecrementableT>
inline static DecrementableT pred(DecrementableT x) { return --x; }

namespace detail
{
    template <class DomainT, bool increasing = true>
    struct successor;

    template <class DomainT>
    struct successor<DomainT, true>
    {
        typedef successor type;
        inline static DomainT apply(DomainT value){ return ++value; }
    };

    template <class DomainT>
    struct successor<DomainT, false>
    {
        typedef successor type;
        inline static DomainT apply(DomainT value){ return --value; }
    };

    template <class DomainT, bool increasing = true>
    struct predecessor;

    template <class DomainT>
    struct predecessor<DomainT, true>
    {
        typedef predecessor type;
        inline static DomainT apply(DomainT value){ return --value; }
    };

    template <class DomainT>
    struct predecessor<DomainT, false>
    {
        typedef predecessor type;
        inline static DomainT apply(DomainT value){ return ++value; }
    };
} // namespace detail

//------------------------------------------------------------------------------
template <class DomainT, class Compare>
struct successor
{
    inline static DomainT apply(DomainT value)
    {
        return detail::successor
            <DomainT, is_increasing<DomainT,Compare>::value>::apply(value);
    }
};

template <class DomainT, class Compare>
struct predecessor
{
    inline static DomainT apply(DomainT value)
    {
        return detail::predecessor
            <DomainT, is_increasing<DomainT,Compare>::value>::apply(value);
    }
};

}} // namespace boost icl

#endif



/* succ_pred.hpp
dLtJPv1FZiydBtOjWjsxm71is8CYn3qJ+SBxoU9aT7az90y+CP860iNJcq2a3WrAHvrcwO+NzGsxWYzF67VSdlnzrHzXtfllfGvPvTtaXmX6bGH8Ffr2j1Mvgg/4bigfzqlwP7DGlYPVLNeu7itvtOtT5b68P4ndzcmZWmQufdoOsK+s16KA/2rElM9i9D1ubLW5h8psWbZcUKo2OL7I2C1xavNE8qPZk8TnLe0X87Lay99yPiMnsZ4u5l2Wqcbk2LdD+TBSvWDvw5nkx9OJT77U12eccfI/SZ7P6CP3Y+SYa8eZs1u7n80fJRonF3f14BO6r7TuuS35jd6rhuvvb81+9OfvL+TA6eG+n8FHrayDzbgv7HPX8sPny+kwtpsYD6wlp7saYS9Esql5PXkT6D3NumQvsH7jVHLK5HadmlgsZ4uskS83yD2jxNxsORClLoTnW/ZHd9HHzxXWeXYy+DMOt9K7ROxWYzPb6q1ZHaNOOv90nHy0XjPxXETe0Vo+lYsP0ONwh/C5W07JkWtGOI+UL8bdZd6J1lsu/pEl9KXnkQo5YVyU+CWyNdYenGROC3wubp3JfZmeJ+e7po0Yww+R6kYX1+Kd445yuTmeX4xtSvb1fNeRzMdK3XflUG/x3luiNecNcRqtfaZKbMWohq6Du8oPx1ViMqO7WtWOzmQlu/a+Ojkz397syC+u/ezabufPt7dX2bSEnOhhciybjmr/Iudd28rpKfKLPyozxDhLbY+Sx/XqQxaZ8r1mvHyvYytdPhipVpG1nozP2tPb/Fkt7fVoOT+Nia3J5ZvCsWrLaOukqT3Gd9E/tqP1xew38n8dSA86tDSnH1lN+rIth3/Mu8L8Q3R/0PhXzX+OnDnWnak/daJ8y1ITu4lDobhnyBdj365TZ8NzMH0eNnZ1B7lvzeNK3Ousd47jK6Zal6zX5fYQeVjl/Hb6FKfbQ9plQ1yL9OxY4z4WnlFH0Cc8U4rTriwyyMorl0vWO5PMsmzyauhUpV4V8xV915+uFpJ3Xm9+kX87wv2xwb5jxxzxHCrXEsMeH0jeJL5PkIvVfJ7EZ2yJLrCXCtnYg44t5aY8v9vY0+V0O/Omkb0k0Vr8da99M3u8vOnFTutl9qEvH65IVkudH6BLs/b05bd/yDo4Qt6JYV3Yf+beox7VjDGX/Pu19/W3Z9maWs8v2k+7iTs/9KbznulkdhYT5yP44UJtDL1bhWc5sV8s314yrx2m0GGUeMzPpRN7evRynqXfesePJmeSNei2odiecj4sU+z5uaPrt5J5MluXxaoH5j3dlcwydWIiXUrVyxj3ejHIsmeeSZPn4Qcg+lVgp5jmjqbjYPEwb08KW8P3Cb0RTb6+Fn3M1S7QF+24v+NO/djEtq1l1hODDuI0SyzPbyWWU9TvCvEy/kaMH2fPlOoz/glsw440Num/XmzWlfO7+LQ3pqPjF8L3ALgkz17JonsUf45X8+vp4fr8eHPosLK9/JWzI0fYq3Qo7i+P6TwwxdolfJzM16nqS6lcNaczGQPCdzPpxohpEZ/1qaCzNquBvNOsUUUP+RU/Ws2R383C58K29BjMH+GZiL9v6WYMvbbQP/wVX/Iw+xwjzLlKXSkI97oY9biMHGNjK90Tw3cVnfi3j9qGOrrf7PpZ7cRRzJ6jb2vrRaWTO5C/xKVW+yibl8qzGvMvoHuJdltrtbdavOTkrLbO2TCPflOz3ZNr3K/l7bfaIfripsvj/tYJ91z2l2kvzBMH61XwU8ti68ubt+TWcfTeQO5nbB4zVO45fnGIdcN3BKPUIOPW5aj12o5R9G8l9qeRR9ek/mJg7Anaf3PZoW8Q/X+NlhvWKrbmTPn4Yxs=
*/