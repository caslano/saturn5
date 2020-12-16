// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_VALID_SELF_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_VALID_SELF_TURNS_HPP

#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/is_valid/is_acceptable_turn.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/self_turn_points.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/policies/predicate_based_interrupt_policy.hpp>
#include <boost/geometry/policies/robustness/segment_ratio_type.hpp>
#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{


template
<
    typename Geometry,
    typename CSTag
>
class has_valid_self_turns
{
private:
    typedef typename point_type<Geometry>::type point_type;

    typedef typename geometry::rescale_policy_type
        <
            point_type,
            CSTag
        >::type rescale_policy_type;

    typedef detail::overlay::get_turn_info
        <
            detail::overlay::assign_null_policy
        > turn_policy;

public:
    typedef detail::overlay::turn_info
        <
            point_type,
            typename segment_ratio_type
                <
                    point_type,
                    rescale_policy_type
                >::type
        > turn_type;

    // returns true if all turns are valid
    template <typename Turns, typename VisitPolicy, typename Strategy>
    static inline bool apply(Geometry const& geometry,
                             Turns& turns,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        boost::ignore_unused(visitor);

        rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(geometry, strategy);

        detail::overlay::stateless_predicate_based_interrupt_policy
            <
                is_acceptable_turn<Geometry>
            > interrupt_policy;

        // Calculate self-turns, skipping adjacent segments
        detail::self_get_turn_points::self_turns<false, turn_policy>(geometry,
                                          strategy,
                                          robust_policy,
                                          turns,
                                          interrupt_policy,
                                          0, true);

        if (interrupt_policy.has_intersections)
        {
            BOOST_GEOMETRY_ASSERT(! boost::empty(turns));
            return visitor.template apply<failure_self_intersections>(turns);
        }
        else
        {
            return visitor.template apply<no_failure>();
        }
    }

    // returns true if all turns are valid
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Geometry const& geometry, VisitPolicy& visitor, Strategy const& strategy)
    {
        std::vector<turn_type> turns;
        return apply(geometry, turns, visitor, strategy);
    }
};


}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_VALID_SELF_TURNS_HPP

/* has_valid_self_turns.hpp
PI3NouOxY2aQq+y7j/1Rmk/YpvEwX4SePkQ7Uy6yfswqaIPRFaJXIX9k5KgtBeq+MI3HIe2i6mlVS+MB31cPcucNIRidOmPtOI4jDBpTA34IihbijXog7Yvz49ATVFcrSWPKIbdNlb/RRBB95tr50pwJx2pluGRTTCtFaXEfDd9kOjH7orDsPg/AYKHgULQmg30Sm79aEBXYDJhpPqfH3SuBf+Ex0H+Dsr1At32rtexmJjtLy1qY7FwteyeTtWrZdVtR1rKIPkyuWJyBGirdQdAq7YVohzT6isW9ECbqrwwC+nKoj9s3Qt9b5+MhWvazfpJthnCfBRmowsr2a965PSTbCrzfg2wn4/Wch7x19yBZUvOuZLzRDchrP46lAbw1a8BWGe8CHfZxTDZ1Boa9616SPUKn+8GTSDauZWfeg4XVsvWMF+g0XsfSqGjexxjvEpAlY/m7VPPetoJkj9fxvY/xnqK/7f5MdqN6vQBkNx5Dsqfp+JZtJ9mztOw3LC/bddjP6rDnafuZ2DyWy43NZqswzA7BcKrwt+pBw2z22HgNOs5jczM5qEyzAEH7VAnyxQ3tuCbJwmNoE0tffratYwx6QWNzG9rHMjO5zo6x3v6WxIFE06LSDSvZsckQA8IfU7DFsZjX99qOU3hIIFMpgFtJqsteZvK5Alz/YqPELLfA2zKF2Ty0QxemO1s3dXRsat3QOgYPceQwek2DA4GlmXKhmG8pw6Hi44/BNNZlV6xLsoRaoiCVfHVsNF9RU94A3yn9ieHg5xCoa2o+EEbwU+XyAozs/IzeUpAdHvEYRbgfBdqPsUKQLdbwPbhjtR7qcmtBTnUr6qgBLjBWaz0qxoUZWBwLKBR4CzMwpkWkWNjQ1enR+uHToF9v1fArbW/1LAFsr5IZgsQLaj4FQlI1gCj+naHGZu98wLFMtTgzodqJE+qVOdd9Yg5vV4piGshXdx4Ym+1o2Vifsy9Qp6BzvcMjjXH8T6kP6W8wJQcs7pty+dlcYbZ+6vuhu186FI61tY6FuWnFa7K6WGwI+EG84QC6xV4w3H4dbnpGpo6mekszM6WAfyeUvmaUC1ANYOK1MFlfD4SjG0+nulrTw71Nt+l6APfKlsd2VMAlq2NXIUTyL/LENjvw4B0cuR8rZabHkv9UXXjophXrglKxNAl63d8BPwdWrBvMwc/hdSvW9aX37lC7iuBk53Cid0QJwPJ29Pch1KvmOW3dB9HwSK/61dffD7+ACX/oMOld/YM7etS0F0z6wTnawf4edV5D0XphhlnNhvUqQTo1lOjd1obyvqF074ED0f+lR1Uk+5MDG9rVfwdGtrH/iYADQ0CD+PsXwerp7x/cn96b6k2PwgrH3mRqb89I725ChvcNjCShO9+f3DHcM3zQMsDf2+8ldnJETWUODsNBlB37dqX7E6OJfh5plAUQ9wykewZAb/AHSAdg4Xh4FK5lQEbfhnb8AwpZfy5Gb58QTmk55GxoW5Q6/Q3fohB1FGbPyOCQVjpooy8JR12G4eom9R2ggL5EpGG4jCIxrCLsS4y2tZo8wm/Q0r4h0HiE9G9ra+Lf62i2da61s7WdpMmEEnW36tiA0RbFB/lPARv+hu2TfcmokHeDHvph+hOLNr1jX7K/b29P7+7kQCKd3jbaOzI42J/qa9s4PLI3iqOvL6lKKgVht+H/QQpdkQ729nV2pOmvVHLvvn5VGKIMNiDuZMD+weE9PcOD+6BQ8DtA+bYOgyRiRVa1JzmUTu50Y8fiVpraoT9kILE/nerbE/3P4E647yPZ048fF33/jsRIT/THzgOR3Q0NJ0ehNkQENR+8DWLq79vQ1r4DOPuiepYYGE3vhIeuQV0=
*/