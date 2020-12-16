///////////////////////////////////////////////////////////////////////////////
/// \file core.hpp
/// Includes the core of Proto. Not included are the contexts, transforms and
/// debugging utilities.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_CORE_HPP_EAN_04_01_2005
#define BOOST_PROTO_CORE_HPP_EAN_04_01_2005

#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>
#include <boost/proto/tags.hpp>
#include <boost/proto/eval.hpp>
#include <boost/proto/expr.hpp>
#include <boost/proto/repeat.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/domain.hpp>
#include <boost/proto/fusion.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/extends.hpp>
#include <boost/proto/literal.hpp>
#include <boost/proto/generate.hpp>
#include <boost/proto/operators.hpp>
#include <boost/proto/deep_copy.hpp>
#include <boost/proto/make_expr.hpp>

#endif

/* core.hpp
rX0kp3M48JD+J4NkDFbnN+EzrL1nxHF9nAv5eYb/UieDlxoTkt6TwKBWHb1Kv9MgG7/r+zkdZPeBTu6WULDzw3Pri/37bCwMbb6f5Pge3OPY3oZ4YUj3dVVQ9qkKmYCXD52wieMzY3udXOSxA4hZQI5orBvLkA7Vv+cU7h84z0OJ56XVTf+tFVwVp245p9rzd+Ayve0nJS7iE+qBQ2OK9qQ+738+n0t4PjnEsWOCuYTRWlxYbOB/luNPpXgCJ80xDyr8wdLgYD1v+vufZ615JUy3pMiQHlkUQPYxw8XESnzVLoPubZcIfKYyR8ZHlfmtXSbxAjzRk4eyzPjkoVFlLndLy5+f4VAHrtA2qxviz2pl9tplIqSsj/FGAqtbs8yN7TII4vBDiKuuGy+j+vlVL+Dj0kEqREha7Gwt8ta3jL/kTXxcDkI7IXUPLGTg2+cMMeiy8fMw4CDu4HHbeU7Y1Tm5ON0JvMzeRnRrXOHrOijaZy3a0FcdPPkKWxknSCNpP8+inQV5F2tMAHw12RnudzntQ2kY4r3GOHEWThFl3sbb8v6ewrRC7gq496Dt7n9qZbjc6Lu38XqMxwnO0MLEA22Jae41vJC3z0di9yJ2kVEfx2Ij23feal/cQT1K9IfAb7Rvitd5skBQWuxi4grcyTpdh+Me8tMuFAIyly8N5ycP0HBr3JjjHvZc9IQPBOAeGBufsPeDpYWblZGP5MaFwB0fm5iycU/YdSiRIMTHFN1idTC6zqLb6ULo0i5kc1Qdli3cOMQbqAjrAe6IOmxauCkSZEF5twXuwbHD4zbuWQs3yroI+ktLgTsxduSQjfswCzfsYNTablWHw4emxmxZe4wla3goJshwtlO1bfIg9G19jjwd+Ew/i6w9OTyOg0X08qZW0Ab/RRZ+DMXRxfNUhA99U8d/nYXvpwWeI/UTwh9Hb9fwz1v4WcfFOW1J6FBNjfp/0MKHKscFgCSlAgenGvQ/a+HjVLmT4PCc8CfHD9Txv2m3N/KCOAmpf+574NDBOv5PLfzIE/mew5Twxw828P9g4xdYurtpV+FPNfBbt+L4adnBxY0wIHyITh3/Igs/66ZegVNZwp883GjvtS38OPUD7CFpABZGtHefhR+VAWxCr0v4I9o7ZuP7bbQgSxV+s71H7fbCIRQXXkj4I9ob2+2Nu14SZjnhj2hvj+NPJdjFpbBWBf6yEX+Gf9LCT/MUUQlBRPgQ/zr+qoVfYgccIyxC4kP8m2uWhY89cwATICH8EfL/SAs/QFLIDgwAiQ/xb+A/2cJvh90cCtiX+BD/Bv7z7PbiZeog6cr+IfG38V9l4XcRm4wpIOsD8W/iv83Gx5OW0Fc54U818d9v4eP4CVGWXVl/En97Hfuk3T9hhNA3iBvQjfQr2l+12xrmLpSJ7PuFUW39oV33Ns75EdAs8Ue19bc2PuL2ulA+hD+irX+38KtsXbisIvFHtfVyt+b4nSBKoZ0leqOtezluijSJOIfDRaEK++z45OQBIq/fq30V+aVhDBm/tInt/u5+HtsNe6jjJ4hiXluqrXvPsu5MYmfWLREdBTxlGEKlKJongWtoIv2Z34G9DlwSa4W3ZOFhg5GISATgTdpxkD/kdTyCfX6nW2Yu7XG8BPjNHI4v4rQPxREWu6yDddrsXkx9X/Z8q76FH2VF3IXNS/XVcrDfsilibGhxVaDas0zCbGvkdvwLx58K0xLbrUCi0xbHxt9zG95OHFQilR92/HAQb6LSWyQJBv+qwGdzpBu54pxd2tSmQgb/+hY+7NMy7pbIq4pDaKMDGf6tLPwCz0xkuGZR2dUj6U9Y+D6yEUOndSV96MwGfYfjH8YN17CNlG9ir2E=
*/