/*=============================================================================
 Copyright (c) 2001-2010 Joel de Guzman
 
 Distributed under the Boost Software License, Version 1.0. (See accompanying 
 file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 ==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_HPP
#define BOOST_PHOENIX_CORE_HPP

#include <boost/phoenix/version.hpp>
#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/is_actor.hpp>
#include <boost/phoenix/core/argument.hpp>
#include <boost/phoenix/core/value.hpp>
#include <boost/phoenix/core/reference.hpp>
#include <boost/phoenix/core/nothing.hpp>
#include <boost/phoenix/core/function_equal.hpp>
#include <boost/phoenix/core/v2_eval.hpp>
#include <boost/phoenix/scope/local_variable.hpp> // to fix 5824
#include <boost/proto/generate.hpp> // attempt to fix problems in intel 14.0.1

#endif

/* core.hpp
iPZ9WhoUQQ1sgz4Ivi9LhhyohmbogWGY4ruwKgi+32qBEYj3XVUeVEELdAWPU+j3FVyDHKiCBhi4IjiB0l/saRhiYARbnfIwMnyMe/j9Rmox+Tchj3rG9wBjwfX9LyB7jjv4dx0UQU07fe7hvpgAQkPm55FnGu2FeL8VqYBm6PN7kCTIg3YYgMoUxhW6YAhife9VCnXQDoMQ/OavFtpgP6TE0P/gt2VnBr/Rgono51mUB03QDSMQj61mQIrfJ9VCB0RPIQ3a1BuROWRDFbRCH0TH0lbIgibohQkzOAdZUAmTzuFeyIEqaIYeWDiTOtG/grmUB/0QfD/ZOC0qMNhInci2GlnH+81GOTRA8N1hKjT4bckAdCeG3ltnwFpIb6eeAXgO/QnOpcF45jnuodzyAfJBZyP3cS69ifb00uY99B26IBp6e5AtaTFpI1SQp/YJ5Ax5EP04ciaNgWauJZNu41wWxHNcRZpB2k+aBGm7aEMn7SWthoqf0xfSVsiDhm9z7j76xPmedriXdnMur5g2krbtYLxJh4Jz7g7aAs2bKJc0g/taoBdy0NEUGN6Mfwmeu582c188x1nQDsNN9BOqN1M+aR2MkLe4mTLJ37qFsWim31DJcSppJmkS5/Ogm+MEjgNbKAM6b+T+/NCzq3QohnjoPR35BL+DnMi4XEC9rl17YeDLXPsKZcKk8+jPW8gHNWvoK+SU0I5b6GsZeddwneN2GIQqzjUD62meF4TW9HnB9TTn6oLPAPj3EtJyiONc/2rKWRN6hhEPddAGOZAOseQfLuM+CD67WAgpJaFnA72loecacaTTbqDeXORN2k86aSzl+t1o8Fu1tbAN+iHmbPoGeTB8Dveei4zeEvqeIxVyIPsy7oGBy7kefH/6NsomjXkk9A44gXQtsWHqbOIVfMuEhmAsSUwI2VAOtdAaPCZPVv6YQDx5eoLnOe6HwBx8GMfTSKdsIGaErDnkJc2ZT3vI00gdVTiORuiAoufow0Po1DdIg8+dfKbYDZmcK95NewvQj+D766AcYoifE/GRweeDtDnpq8iFdNpHGAPy1UI8sW06FMEErtc8wnn+nRn8dz7nNqLbtCuTtJvyW7jWDX1cX0g7+wuDzzCJF7meQJoOebAWGqAN+mAYphQiE+iCAPfGQ9M92BaU/pO984+rs6rj+MOGioXGJhoZFRYzKjI255y2EjZwwzG4MaasVhc27gaOH1e4uK1WUVHNoqLCWkWFiYXFChWLjBILFRMNlRQNEw0TixJzK0zM3s+9n+fHfe5l2at/W7197n3O95zzPd/zPed8nx+XQ13THGe7qIPPQcrvQc8Bjl21zD18ProH2XV838v5HUuMzu8wj6zAlsTyudfiCxzzoRr6oIdz4xwnkF2Aw7qXmMP8NUfayDnYB+Yh9R3E2lAEmefSF9XYjGM1HIJ+/jbQOASx80ROgtFzErY5nSOMwVHSdqBnNv4Qwl4d0HMGesMoedLOJaaE9Az8BKrgEPTCBCxA1lnYHQ5CD4zBAmTxe6OB1fQBxwz+5l0/dRzk2ML3wxCkPYf4271DfJ6qRz+O87D/bGLZBtqxgrz0XTt6jKH3HOTSb9lJtBdq4RB0QwW2HeE4BwuUWVsXuZ88hN0yj3EdBdO0o5qjQdmDT/EdjvLbwjTavw5aIed++ohjEuVlwrjZh5Bch40gH6qgBTphECZhAdL5nWQuedZx3AEHoQfGwWggP/ggBJ0wABPQkYNtYPXp5INWOApp9ME6qIBWWFtNG5nn5pHdzzjrhWFYt4r8kLWC8jiO4nPltLUFumEYUlYjB1XQBlOQch7noBo6YAjmwEcfdcIUNkzuZn6jb1afjb6cm4A=
*/