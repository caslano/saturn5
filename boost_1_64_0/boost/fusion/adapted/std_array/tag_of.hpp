/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_TAG_OF_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_TAG_OF_01062013_1700

#include <boost/fusion/support/tag_of_fwd.hpp>
#include <array>
#include <cstddef>

namespace boost { namespace fusion
{
    struct std_array_tag;
    struct fusion_sequence_tag;

    namespace traits
    {
        template<typename T, std::size_t N>
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
        struct tag_of<std::array<T,N>, void >
#else
        struct tag_of<std::array<T,N> >
#endif
        {
            typedef std_array_tag type;
        };
    }
}}

namespace boost { namespace mpl
{
    template<typename>
    struct sequence_tag;

    template<typename T, std::size_t N>
    struct sequence_tag<std::array<T,N> >
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template<typename T, std::size_t N>
    struct sequence_tag<std::array<T,N> const>
    {
        typedef fusion::fusion_sequence_tag type;
    };
}}

#endif

/* tag_of.hpp
I2dcJSv1cWPcsrlJxul4rdXt2OpuTFrQJCQVk61VHlQHxSFvqA31js5Iveda8ce0OvWm9WlAvbem3alkIp9upjvyYWaVmTurzfxZY9acdWbxrDfLZmuytJ+ZeWXuUp0+9dmkOmPqM5uvbZVQIShEjWptWJY7UJydMqnVKxUSkskO9ZtRwdSKreHK0qWKfanjB3ncLyvkMLBcx3AN0/CsOQzfMREcVZJqUrNZvF/xBWwfkmPi3FRvPDLZuGmdc5mTy93NnlxW0ax6PyCXrX63f1KC3b1s1m022y/Jp4nfKWtAdJF3jtDDjDc1txWYFfjfMTEPqsrmzyeDwbg5Dslje9zROutpPs2kMpFsuuTTm9QnPlkNJs1JSG7bk84kmnStXoRkLCJnvel6Wky308P0OHVm1Zk3q88CMtZCuVNbUXdqWidfTCR/x2Q8YJ541YnXRqIE7cQJ4qu60pzmlI1PirVVzTq+ZJYHaHKmVdaPBjOLp9mT8+o8WlMqzK4uSm/rPpmnormwtIclJlq8Y97k0dGcpsmaGUsu+cPwXbPlcbSrl3y+ywyEaZ95CNchK1lkyWZGlm5mZQlnZkI5jHuW8oC5ecxDqA7gWubThm7mZAlnXkL5eTU4Ub2HafclVKPWotMQ7QnRVqOTZbrM0cKt6lJ95asuxWem96Kb7XfNlzwq5OiO6Q5vn72E6YDVrPULTLdVoVKY5pfG75rP0bztcG8Vp3p2D6I5XVQnFfeA6uxRnQqqUxPVgdgWtHahAk7hYQsL6isgoAGjLfgUOlNxGCjQHgWqoEA1FKiBArXOCrRGgbZWgSqWmTrZQoPIlRCdkqkNWdqToQrs1GCncWanBzvoEGQrO0p2k3x1yFWPPK1P/KBFVdSojho1rRp1z36FzFk9qpK7Orlr2tx1yV5K9jZnTaqSwbpkkLW2Qw575HBNDkWVzOFd8xaxNDZHQdIkT7KGbDUHlX6VVaJro78d7YgoSo7bqYwd4vpIEVQL7uqOirurN622xkWu8oGfJNYH1N4ta4NYQz1RtdwT2ZDYtoluRHxjIkx9ovYFMaZCrYKg+cTZk7ooq4I4t4jgYfHQ+wREUuogJo4Z+ocymre0fvEb8JvD7w5+Dfy68OvfGKdmvuBn1qMc8opzpMq30zfTN9mydvE2sFNWuShhG3LWVFZ15YrzoYp2K+PWzPf8zjq54XPl86iTkBU8pzZcaiLqb9H4+sBH0RNR8mFzGLIa58PqyKUWopHkjPxoRjaaiZrqcRfOc7LBLJkhPp54MzuYZmbMqofuoDESX4jN8c6uRE69ZAUqfbhsQWSySCGStcyrmR8NI0GdLU1E7RwxjRYVXtzUqG7hao/LbuCy00GGs3DwFO3hBj9RG3nUcmzjCF2WJxhi1m1qs5jADLUY20iKUpYZTezcUF2ZGxUTytyolnxBXqkFR9SMasB1Ugms0NRBQR3gs/B9Hi4LB4rHitV37lmhjV8zhdUyh7fiXVhpeBNWYulsqBSqpI6TalEjCQqF+2a9bdJbdVll88F+QNeAX+rgltKhvI9UD+9k10/ei7wU9t2oDpsR3k2J4Q21BuQ9yxWCt1ViWBPK9QCVcWZlRaD/Ng7VhYtaRKjEbgHXaMHBvj8vEtZMojnyqHrJUcyqJDk6sH6SI7JD9yjvQFbkHZyhvINPbngLsrOl+/FQXZ8M9eiAciXeqkGpArreJqhpNjmQE4ec0BXYjNhqo85i1GrH3Cqrqrp85tWumTd4yIpe9o38y6FmvuWRQxk1izdxVPd88hqq8sX46ky1b8f7snqhfmQcTxao/kVkPVEFLPD0knn5dJfs++S/Kd0HFYhLgwHmxJq2gwPYNu+Z+qs=
*/