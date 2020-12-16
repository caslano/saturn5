/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_EXCLUSIVE_LESS_THAN_HPP_JOFA_100929
#define BOOST_ICL_DETAIL_EXCLUSIVE_LESS_THAN_HPP_JOFA_100929

#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

/// Comparison functor on intervals implementing an overlap free less 
template <class IntervalT>
struct exclusive_less_than 
{
    /** Operator <tt>operator()</tt> implements a strict weak ordering on intervals. */
    bool operator()(const IntervalT& left, const IntervalT& right)const
    { 
        return icl::non_empty::exclusive_less(left, right); 
    }
};

}} // namespace boost icl

#endif



/* exclusive_less_than.hpp
WUk2ufkDr2INZX8TC5746gn/jI2s3p3HkRsN8CYoX87IVbgjzXD5qt8KBj48jkcKh9ckDtB1yeStYVZY2QzwTFaW9q9C+Gj8We7PKsWDRiWmLPHH45seMMxqhpn99KT2kj1UWZFNtS4V/Dfpqjjn4Y3dTX3Eqmm70T72nnAY8g+GFRpiRLsvGKx9nV8LgtDEJV/mVN+ncepxRgz8hKxiAzYtUcGOEWly9pc8VOT1xjADfSatmkdlvZc0O9sVnom/4LvanptsTZAc/gh2qrXQ6P5BnF8VwaBT5fLfwSDufT8QFp+ac93SjXLOr3300I2RT5vaw3yvGT6oJXLkf/Uy7Zk9ZkWUyokRV+H4zF2qdTqLT1f74Pq6MDaoenGphyMaLE/hlmYJtZo+FO8dP+Bg5H258pQG/ihmWNoGFabJJXJks3EIKLqAyy6R0PPRlFtv1mPPuUcy9PIIRnw+j4jFczho/R7R6+kB3JrfX85qG8DCMzZ4cTIcaqq90fPpItq2qxf31L+y+Go5hh09R09fV1a5f8F0Ywc5sb41tc9Yifa+5ni7IZEXxmtzTsovDLTy5MbwOfzw2R4/CrXkxEFf+OaCNlr+acElQxz47fESrio/LXpkPGDWLwuuU7+GYIv7jGq6nz5j3DDOfT0LRrQXSrvmYlZwLUMN3XCyywWcH6YFzxHJuGP6gj3ECmEywAIZTROYFaXgZIF95A2/PjT1aylc4l9zwKP/xPkfx/lTwTPW3AWaOz6WmwLTEVD1i1EJxbTT7SDDqm+hVavbcBWl6NZHGQgdw4+Wz2SfYAdav8oX7jq2VGl+mz9STXnz5GCRHhnJVTd2yoAzPdB0yj/5QqctbnfREpwYRY8gXzxyrMeO7WNlHwslHFzzFvFW63F74XT6GjvRVGWgiDh/GIMjb0KNfdB6eA9hMnoBPbOmiRj7OoT1CxdnlRvw6Km+XLHZGh8uzEdKi7/okWKC/qe7Y81CG/re3slrZ7PlK08jZKx/ifo4AxhccOSDVvY00kuSWw894ugKDxg8n8dGJIhWdpexN3SQcFr3E7MzT4tIh2ygpTu6O6fgv3ID8fv3F25PMaR2x1xOKisSFTaKnj60jKcmX2F2wz9FvlCwksVbaHniGraGBHCHuyurr5xgrbstQ16Wcmd4FTK37xczjMI452Qys6w78Y36Baqr3obP9gLueheNYXWpijNIZfuFMYLjzBQ+fyR/1DXl3zZRiJtbzMN5wbKhoisGxzbwtNEV1gz/jN07trCTrBXKD7IwxnUKntUk4FZOD+FTVAutSW/liH4VnHrZU4a3sWPR9FC+vFuArV3C5Jbmjdiwoj27vpiCqW9HyspLY2B++qY08HxL5aXTOOPUF+zRmku9T/7YF/ROmP6yRePg16yZ2gvD9rWT5boTMSFYQ+4+5IQeh5/LwgHd2ezDb/nvnCr7oof8Xkee0lOWjW/r8dZ7KzhESeEn0oWtUzTnPbWRHw1OsvArRJHRB4b4RdPrwW3MOmoolaLHo12Core62mNLc2txca0hfZzHsMonAzc3hjLcrxKXR7mKIQ+uMTnRT+gt2oiOC5Tk3v3OXDviAJ4ucMcez+7yyr56fHk5GH8e7uMoZw38eH8Mlb8rOOl0e7rVDaOtmyPN/euEzTtV9J8+kPVPkvnCoKO81VORJz1NsNiqDzXsbWW3rqrM/vRC1sXkoGR7FZ5vbQPnsU+obvablVv8haPmNDzONZAzr4fiwusdYk87J+QODJOZqa/huWAPo8ck8Ln+JNk+whARerNkmk011bbZsjRbcRddO3Ctrza99T8x4WMsn3dWgXff1XxSEIx7xUe5JshJ3n/xmlNK6kXjmos=
*/