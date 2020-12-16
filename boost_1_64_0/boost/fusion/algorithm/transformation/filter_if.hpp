/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FILTER_IF_07172005_0818)
#define FUSION_FILTER_IF_07172005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct filter_if
        {
            typedef filter_view<Sequence, Pred> type;
        };
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::filter_if<Sequence const, Pred>::type
    filter_if(Sequence const& seq)
    {
        return filter_view<Sequence const, Pred>(seq);
    }
}}

#endif


/* filter_if.hpp
sKv0MfrPbNuwmzxT30H6u9aEFwnyduqWa5bSzhjFfkbp24yUsfhdtZJ/cbtgFoZtKEvy7yH7gi5EVyXBrjv5F+delm3WmH9DyV/fLumWInTjjMr2RNNgK9GXzSLP0h+Qe2H3Ed7MLNCkbBxmlHq8WkPyk7IZ2ruULTKMtS/ttoRyBxvKLWMEaPs0/XK4yo2+15xJiz+icl0w8BVtObRempOAMrdXXT9tcj1J6tfkPFzGc+BZEXWmVd3UclVApVx5r1nLpdwQJCdt0neWUqa8EsvEtU6p18W6bT6l+FRaps/SzmOUqlCnT7OZPiyWzTqOl00zvX79JSaC9LE2x6+GPjVGtgl9vRi390RlQ5V61trHTK3NGo4ZlDJGap9RPt1peD21j5B7edS3jTjJdSU32kU+62AG7aj3bupc2mjgnXM5aWva71r/oR/7w9JK3isoh5vPEw+ybAV/s86z+EveUrcPh+dz+nuKHJSRJNwHJPciFfcxUr4zUr7i9977Ea9x0Jn5nlY+Nq3YaVMTY6bHRUWWuY+R/G3yymytTugq25qLbGtOeda81C8+tWFh775OPA3t2jherrJ+C1nujZRnDZ+FW/OXYwVDG6f8Ntula1tr/twazvQ4C639xX7dMihJy7Rvq1Tr2fet6Twj42np5v2H9I3Gdapv+8b7yyJpDGbvIzfWTwQVpLb3bdTFHhY+hcLUPyDHB1IfMn5lWKLySvmwRF7fr9aLck/XEJm2AXWg/L5Tfm8kv//d8Pst+b2J/O7N8svvNmO1xLaT92W6UGZ8FZV6Dj2or2el/2PvksSdkDEUS+o8upQ2YzG2GZvjJ4s2NmaIsX+06atmzaE+whnchjNc8pV1JPNIiE9WDnRoynLYJGNwGs/9DMcpMXJMqa1r63yDdP1XbPy8qda5yxdz1r6KNhlNfX1LW2x6iPox3ecY27I8YMLPYXkmZT82VLbHD/R1TLO5y2v/0j8a7nnU9w/y/aZ9u4ymxg3HZzHasZ+HSfu1sPyx7dXj2wnHbbdnqYO5oLXbD6zLyDX/Hrb9YaA8kDlP+usEogeFSMu3rRO17d3ddbjitvAvrZ+hqUgbCdQ+JxP1YzmvoM60z7mqIvOx7a/4g6F/d+so9xjLsfktoicF9vjQZnkkK1ke55K/e6vxEWl13735Otv3V8OcHfVXtEVdO2jTo3iZSGsoe76U/RVnGccNe1N2y0eGsisHmvd4TdTQRvXvB4tPknN9aU9ybGlRcjXuW2zG88zopGZ+SM4f8uR6SXqBrvzKIY58z3+v25nuuEq2f33bkPIbjq2kbWnHcEmUKtKwHpI7qwV4UvbbabLfTv/EuBzK+VliGfZ7hn2c+fuBtL7w+57W4zlZf/plUqfxNI6Fb1xG234gytprGJbxlixjJdlOnLAvmad9pl/GqNiksKncRF7296nJ/lhJaGhrzMZwzL+Lgis/l+T7gG+JfmRScEJXBuuwyaUfW9Sw/a5bjqH14ygb9z1259CyDHJ9Q74vsBnXrovx/nE5njupK29MZJnryqw9GMvbxsGxZZ6UpYdsa11kW/P93KYs6lX4Mpwrl379ljlFKENP267DrK7qTOpKn+WOdZRtRcqhu7nxrrb1GrbnHOp36KXuT+/cw3CQitlGGTcp7Ustk7GvUJqJab+mr++gbjKukrTVDbJfKTqlW056A/VQ/t76Zvs+zHg9SF9WNUN9P1wkZQ2TsoZIWfO+0JWVOx45yZnDC57Cy/reoLKW10PXZoxjpV7urs7UW45zO8hxru9pXdmUTY9hKOO4fMlBR1KilG9pCeVryH568hl1P209XlRnopxmyLMu9u3Ky3COdJ16u0D5vuK4cNE=
*/