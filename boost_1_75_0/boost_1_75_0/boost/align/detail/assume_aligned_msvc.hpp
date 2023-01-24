/*
Copyright 2015 NumScale SAS
Copyright 2015 LRI UMR 8623 CNRS/University Paris Sud XI

Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_MSVC_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_MSVC_HPP

#include <cstddef>

#define BOOST_ALIGN_ASSUME_ALIGNED(ptr, alignment) \
__assume((reinterpret_cast<std::size_t>(ptr) & ((alignment) - 1)) == 0)

#endif

/* assume_aligned_msvc.hpp
lIVylcBIkINhUnJrq7XxI397cfCkuQV3bFAwqodCDa2fpPWvqBLe0zx2wPiO0DdjDYhdw0EMRSHqw3hLCuZgBy1J1Kv02xUSvqPPeKEuAbgdwt4KCK7T6yEhSDhQ/qZTVkTRY0c0YP50Y12wXj8kRGCocdP5HTqGV2Da/5M1br6g8gjrdNbQltPscaTCvBth2mIVk6OrtxElQe2hkl2ToT3LiBC4IzKErs3iFcs0IMx1SBgKNiHesTXLz6TMXeCip0s3YdRtW5Eg4XKMioBfqM/b+6FG1nxFQFp/ydhdPg9ba+Za/tcQ3dzElW49B+nsbw5wBraY4dc1djayZOOvay+ctm8cGTMkoYZclOuP37tRytMXxVe2nhTG7XBOd/i0B8ssoWR25eNqTNPx1p+A4SazxRl5ulFqo0zXyu6od1VfXP1F8bz9g+9gRx7pYnTIP0mIIylHLVooSHkh+a+TWvpjhyGEhWfQ67IyRegraBynMSMmAlX7IwV4EcGVY/hHPV59bIejbAcNQpdRQ9VVzrpYDazir32N1OB1mgGqOmUs2l4YufmgNG94AEvatSPsGZvJvgtqOvWL8ogTMuWl3WM3OoPPmiJ9N/XR7r4AWBqXldLXaKxjKCE6fa55dGpsAOQFzrbAmWcp+LbwTOsBm/wRosVu7cgdSo9i/1NSMRDRnwSiTBx1/6MJ8KOf5SIHkO77Z1iPPOLfXCJb
*/