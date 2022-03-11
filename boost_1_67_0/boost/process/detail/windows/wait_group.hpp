// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_WAIT_GROUP_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_WAIT_GROUP_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/windows/group_handle.hpp>
#include <boost/winapi/jobs.hpp>
#include <boost/winapi/wait.hpp>
#include <chrono>

namespace boost { namespace process { namespace detail { namespace windows {

struct group_handle;


inline bool wait_impl(const group_handle & p, std::error_code & ec, std::chrono::system_clock::rep wait_time)
{
    ::boost::winapi::DWORD_ completion_code;
    ::boost::winapi::ULONG_PTR_ completion_key;
    ::boost::winapi::LPOVERLAPPED_ overlapped;

    auto start_time = std::chrono::system_clock::now();

    while (workaround::get_queued_completion_status(
                                       p._io_port, &completion_code,
                                       &completion_key, &overlapped, static_cast<::boost::winapi::DWORD_>(wait_time)))
    {
        if (reinterpret_cast<::boost::winapi::HANDLE_>(completion_key) == p._job_object &&
             completion_code == workaround::JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO_)
        {

            //double check, could be a different handle from a child
            workaround::JOBOBJECT_BASIC_ACCOUNTING_INFORMATION_ info;
            if (!workaround::query_information_job_object(
                    p._job_object,
                    workaround::JobObjectBasicAccountingInformation_,
                    static_cast<void *>(&info),
                    sizeof(info), nullptr))
            {
                ec = get_last_error();
                return false;
            }
            else if (info.ActiveProcesses == 0)
                return false; //correct, nothing left.
        }
        //reduce the remaining wait time -> in case interrupted by something else
        if (wait_time != static_cast<int>(::boost::winapi::infinite))
        {
            auto now = std::chrono::system_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time);
            wait_time -= static_cast<std::chrono::system_clock::rep>(diff.count());
            start_time = now;
            if (wait_time <= 0)
                return true; //timeout with other source
        }

    }

    auto ec_ = get_last_error();
    if (ec_.value() == ::boost::winapi::wait_timeout)
        return true; //timeout

    ec = ec_;
    return false;
}

inline void wait(const group_handle &p, std::error_code &ec)
{
    wait_impl(p, ec, ::boost::winapi::infinite);
}

inline void wait(const group_handle &p)
{
    std::error_code ec;
    wait(p, ec);
    boost::process::detail::throw_error(ec, "wait error");
}

template< class Clock, class Duration >
inline bool wait_until(
        const group_handle &p,
        const std::chrono::time_point<Clock, Duration>& timeout_time,
        std::error_code &ec)
{
    std::chrono::milliseconds ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                    timeout_time - Clock::now());

    auto timeout = wait_impl(p, ec, ms.count());
    return !ec && !timeout;
}

template< class Clock, class Duration >
inline bool wait_until(
        const group_handle &p,
        const std::chrono::time_point<Clock, Duration>& timeout_time)
{
    std::error_code ec;
    bool b = wait_until(p, timeout_time, ec);
    boost::process::detail::throw_error(ec, "wait_until error");
    return b;
}

template< class Rep, class Period >
inline bool wait_for(
        const group_handle &p,
        const std::chrono::duration<Rep, Period>& rel_time,
        std::error_code &ec)
{
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(rel_time);
    auto timeout = wait_impl(p, ec, ms.count());
    return !ec && !timeout;
}

template< class Rep, class Period >
inline bool wait_for(
        const group_handle &p,
        const std::chrono::duration<Rep, Period>& rel_time)
{
    std::error_code ec;
    bool b = wait_for(p, rel_time, ec);
    boost::process::detail::throw_error(ec, "wait_for error");
    return b;
}

}}}}

#endif /* BOOST_PROCESS_DETAIL_WINDOWS_WAIT_GROUP_HPP_ */

/* wait_group.hpp
Zfx7Pf/CRUmV3nIzP0B1nY42+TQ0sCwWJtWkqpBZv07jvo73T8F9CY5WEO66+5KkkThfwcqX7BGnMWPLuPGexPCXsiIuY0brOCu6Jmv30ik2pbX7XJqx+65CvLDlmwsxs+6mkzi+7i/aEcOz3QoPOO5SRADoLulnlS/LLz4TJmxGHQOYf7L4TZF821ARRAPyw0vYO91uecPfkkZ1dShE/0HX0CtdG5ThYceM+GYMXVzrXr9eCAz3+vXxzdOtV+vX0/TdTXtgNQ6JufFNOB2q45txVIQIBF+vdMzgJq2pXeRFxjn8h/UYhlvkOvy9egyjnch3+Lv12HTzrdRjmAlVGwOyVcttJhZBTf13NxteNUwlmuig16Q/2JsRUr6k8IOv0Ve4YA9Pa/0Ia/4yb+YINsIdLRsl333IFt/EHTSNY7qgyQbhYH8Mk5QVuUNswsBBsWsHRm81N5PGsHhvPHuUTlSeX/reiuaLGJZVcYwXmlJ1k0KgI76t9fPFVh1xwpHEoZL4uxPXCcFFb+Lx2MpzI/yHqOiOeL4dgdDn9fp2RIfF87+EyZzXK3i4fPtoKxCZuRW6RuZEjp/KE7ldLv8AtH4gEArRSRfnqgLWnG6XT+YdU/tY61bzij5Xbl8vn/mAB3VqMQ0qPCdkDKrNGtQFPSPpc7isdQwo/b9cqfRPZzLi4G58zQaDqG4OQGFJnfQac/HF21AZnLERbewGaezfHffvC+iVnXrNPr1mv17TReS42t1E0r8sW/8K6grDE3wyCCkPdQmBH/ZRP14Grr8n9xhbfMJbf0pIVAuaxNRE5GipChYp5AayL+AFGavpZbmO6pFrrmQkqhZs6dYb0TvjCqyXYDyOgK3yd5QoGG/CPW2veOU6bI6XrkOY9m7sNhAPQ3ccB6OI7z+GOrzaBs0hKl8yNjEc9JgOArHeglUIR/EY7EKpVA55t362OUWq6tVo39Er0pEbhvpQSDn9JySXBt4v4bXfdTETqP+6m/50gQL+gkf3hr9DUcacG9PJO2V89yLOWPFnjD3DqKzIBOGXJYbvA1EYyRo4GAqmlSgT4wmELUZUj/nZQeWmTH0oMcKXGwWLocXuP2we0GMsvCw+7/DcIFydTQEXviDCfEimX9gpN8coAXc8vwqxGyt7q0y+am/IjL9gCe/+cjzXjNR4KjKwLIUDAqE2AtND1hGEIEo7HjPM41vOLOUT63Lz8XJ+1M4z0cyap3Jsvh2R/HRuHGCPUPbEuDRSAV0E+GrfQqOdEtPxTJ0SvBJxsXvFgRJDqeSePkYLVHVzlWwTKrvl2Upr1zzwzrUOPAhp+cwT/sMsdwW7yZ5rvyUbw0MHDwZoy7Fclm7K6guTTPpkj2hPBGKlOGZs1Soetnam/OxZWmF9zyY5CHa2GQQbaWKlOJxslOQdJPmjmSTHTIKPhIlkMGC+UpJnq4V+udy/94vcxHuIcJHjpp92JSt1MXB8/rmOZufWwpL2gbcz123/VrvS2xkSkiD1oKwn8y/k5au/TzW9yopne+XRvw/QQ756+JgewpyLHuaAu2N59ceLnZw0WyXdwg9O9fBreoivZY5zCVTl+ZtLfVvNDx710EwPPTAAhZeSZjQBBa8gAjHenG8+PYgnakJIbvfRNvdLvLwbL5kcg9w4xBmcZoYb+GmieoIYaya/cJmfL+Ynj/k0kZ6g/ywjzgYIlT2J3AYIsD5FRCgelHhlr/EqCLcq6sweuMnHrqo5LF5lbKw/MjLms0VMb/UBZ2q/fWsgl50NtnocBZ6UGfm3vsQWnP5CnbvLLkFNyDFcVHpElbN4dGIkAQo3P7mKq7L1x9EzyILLTVRY97si5WLk0g20HNqbdrp/2M4k8V/fHTDk9v3Qte1aTRjWzX8CoV2yE25Kt+qMtxL20QV0u1oRaXMJXc1XSqRnc2IVhAhm1fRBrrrymGG+qp2ZXcAyYBUSbNTVxwyEfCE8tBC4cEZwRY4R45Sd45Im1130yVsnMvuz4ksmFjwPNnxDcOawTR44aRjw+VoLMqp1I0brpWnKdKlPoRvrcdNOfw4QMbhe928RDr3yJXbxBm5cqc1Dm/7OUlsRVJFKCWLbIhNK4S5Fu1uhc6Jyi2NWNh2mtCwIr0y9I+ShExjG5fAkUeYq5g86NNcJE21nh3P0XSbO4u9O63s7x93azi4ndiM2/f2pvdV6HpjhWwTBYl1bJ8/fD2SzHWTJmXzbjVs33QrtJeMK5UmvHYK1VdNoeem5MYZghCew9w8TtbMiNfFYGIGZ6n1Jf3zeBl2j/xuFfa4RCHhntF8x3uNufII+hofHK1fIn6w+btAde3bBWfwYPavM8Sa8I0RhBUxA7PJbV2bblIMMn39D3QzFnvf5N9ZdLKIrE2eIDt9JBFtximsRlQIy1OWENvhOah/1wK+a/PLbAwal9J10N7ZR+9u2FOd7REeTEfkI4XmvrV3+y0KP3PTOAJ+0t+v+fbp/v+7v0v2HbgeykvZiVLkOz7L3nSTsd73+LtgtQnPF6z+E20NwrlG5b6ArMHCgirPyWRq7u9Wmay8b2iEloOgytP2Gts8oaNzHYoqXpZfAHajeVq4Lrae3CiN5WT4+ccBoMtxNNzDqIn6/mP4mpqPX7sYiyLW5E2AbyU/eVprs1eGxsZ1GFf2rXTpqPOuR49ylIelUA85oSsVjx02KcIW8mu5l4FLTuRhhjSG4Pb+NNliKbtPr6T5fry+M3zJNry/S6yfr9VP0+qnyaz/KsZlMqvDkeDOMrkMBeauHDXcWpsisoHnA1zuV30Zvfba7aQ+YCH6nmV0vJxgE4/qO8olwGOjriHgDKnzy2LeZu9gRmaL04hGlJaCmLrnP/DRSfeJYheUTSw7qUWe8Dc2ZjUW6PX5LEbSqOay0G3yBQlE+8We8QTkWS+SCn/H+zAFOeubPeMviQ1Zk5M+wYyOjOFCAE5kJJck3qN0d2XhX/2zsHo9NX+DSF2Sn3JSwwXO2LXKV2blgiAZOvvl4Dh22qll3oCRCzgP5VM5NGlHhgxgOLvwcKumO1MixldiCbHcj8F4aL2+5K7JUL3d5F3gQs4qzgVGTH1IlpzqW3XQwMtnsVuyEPVKoukX3RK6qXrljJxzacOE2mSX5s9GpE476zRiThdroWNtuKtGmOdF8BzU/M1qU1cnFZieZo9SM9gSpxU9M9UAUsy22LW9pZSi+ZS3axhayxcJNcP9ycGrgYFtpIo6j8RhNdHOA0Alj7kR9LYpMjOSkeWqkJsY+zb5p2RYamhTeyIrqB8RN+fHZRSIZ15wc8lA+spcwpoeoaXNFKaY8vgmVd/gHs9EGWg+7KX2gynhfjFJrwWS45cd2ZBuVg9qhsDEk1Y95kFnzoJA5jmZ03tiybFt1KHIeO3CdFHudhyGizLxVY2Jbp62Xk36YYzPZjJQh4qSXPa+uyUlhUhn+bIR/YhDHSWHJO9UhbzA7coe3wHbteA9Rj/q8Pn3eUX1eMp7vjIygk7rYX0RjmHAJf36x3yW0Ikdf9dyA8iFT8DJhh+lAemYYPdWm+E3UprN+mJPGxas+BW4w0cJ8M/3rEMbbTi2Zna1cLAiBoUAAqg02HDlDSRP55adzOPiNaoMKG+duakBGOp05bwmdvHO2SlfovI5AOFve86scs1CxY6scyW9zZWDI21H8NkdelXob2vqJ+7yB6nCevIDeIWCwSmzP6CadSIW0sPJigqcl1dm7PkFnzWPfXMPm5uLNRAtuCXs9WSzKPT6/M1IbJOzWVXJQdMymdgfP24Z2/+qXOWZ60UHt5re58okhb0fx2xz5vdTb4NZP3eedCFG7v516Z+29hXewW3Yl8zVBCAGmW4Mh+YsThpEBOMwtwRziC20MP/5pwQ/4oObbhXdkJnsRr2yxe5w29jI+KzviCQTErMLw2Wm/zYQT/h1Yzu0XphTdcAhgW0scHHxeEBzY+YMcm3RNSVECUZeN4XvrS4cLPJoD6k1Rz+bt9NBkaFniBCFHYBIGZNauASUs2b4Tx1pkAMjyv95ieUqC8I88nGghwkB5nRw0wZnfZQSAkul5SiFmrsuCUoeHDKArnH1HvA2O9TNg6UQ9T6V21vcILEw6v8rz5SzsyI5ylsRlxA4C37H/ZJoPeOLNNB+w9V4ai2099m8fN1nuQ4MwEikP7OtISTsWi7cZgi7N422Gxa/m9DZ76C/t2ls9vpZVdFtX450zPTI/vnY5PQQz91HKt8vYYHyOZ4gHr8gUeWzbMYMdV3iMVxE7IP6A2uWGJoGPghvBQkVrsT+QUESk2T3NBUceIXGMivoVFRVSRb2GomI7rKKcmUVl8NxresbAel3dhn5t3p4KL2KbYetvMx00O6pD8U3osWmBaRpkMYcRZ1HSXr8stnkmctCB1R65V2wCFyhcYBRA48PR7uurmyUEghgb/r7Yt5JZYmvxDr2ShqoX1qSbF2epCMNGLIJaFp/QYwjbpm9azL9P0G/iUjFDaVXTWL4Xj+EL3SRGozjrUZmAIkjeUTEvWTyvr5ZZosWd4GDERTcSEVVwQTXCTZneJMf/MzdlE8ryMHnfOUlTyI6JXwD4QyTtZZQpw1uIq2ErRoRyVCmzhLSb8dezeSSGsZMRMLEzjluTR8Iry02H2eU22Jxfj4Xl0KODQRg7tEBxXn7v68cNflo3nJ4i9GRmK/C28YIc6W3DgtRywtnzobEUPiMQLjAz599z3LjDLPeC/y3fyEB4ZGLy/5ZqXCCcbzbm1bv/18aECGbGW9YUUeoVlDpl78ljAlw2YyjzgUJYor1VL/NH63AeyqEQlGBJtjhgXBGPYfQDHHXW9LDpjHUaPeeBeNnpFdy4SV7hUo0U3LiR8I0S/r7d1sOwJfYc/YZ8W90rgbL6Yquw4uOI7iEEC8emNxCZYCzOji/xGNOGeGw07VAWqzKa2utvNx2nzJNC6xXD41dP8+2NXl+8x/3rdiLNb8x2/7q/uLLvSfevdxa/6djzdtLXGb1AZU5MaGpfeq6qPXqmWbOrIbZsuk0LVSz70Ex1swxuJ+JAk7R8NiOQUf2VTcbSf/o2cz5KxfmyW2NLp9siY2mUYu0e44q0/9FJc3ycrW4nDVMqesHEjxVDQXQkEtYWMPWafkrjRKfM6YEgwXeo3evNYBhmyANTuXf9T7knGq+iT5llqP1WNKQ05aTnQj4R2W/fF5WTTj5nN7Nib2OndswB6yMV20YdCB25k3OJvHr34cHUsXB4yxfEQ850nIH7ivQGbmIDloZynGXqOd18Cx2vx8+2Ikzd8Bv4+ujInU4V6G0Mr9oi/MsQrK2Of5fzbyP/ruDflfy7in/X8O8T/Ps0/z7Hv+v49yX+3cC/G/n3Zf5t5d8t/NvOv+wAr62Tf3fTb7wFo8IBrvbxy/3828W/cAgt385OGh3NSBUpyvco4ME0+zdo025eCfJxLd6pjc+hj26lL/paPMZbjo7mlw55Fb/EY7zl+vH8Mluezy/xqCABvcyRnruZbdAiaV71tQwgfiHoOJ4E0B1rwaAb8Wa1uds4YFdbNrfXyb8u/vXwbyH/TuRfHFfGu/FmDFwAN3wg6G28wtru4t87+XcR/9byL59I7xLFojcjiLLin+nNU/geMEJvBqyKN2PcqbQizjWVf5mn0jaTf6/m3+v5t4x/K/j3Xv7FEkaTMEnctn3qRm8L8Pebs4Aiy/qzgI01oM/05zn1hyOIJg0t5/np4xD5hRU71IuZ46xQMOIHrArrdwqdQ8d4rDgfZoQRDkpFQMopmnvpu5JeCz6a6I9L/clWf9B8s9QGqAuzeU/YGOgCB045NeWiGyanElark1k5VDDeAyB/L/YGtCLs8dcwk7RZIw7CqHDED9UeIAL/N0hhfbHobp5Pm3YhGs+4RlsGrjEyxsNORJjlb0k093G/qBdZqk/qj1P98ag/WAXb4ryjCVLkxpZm27SxQodRhAoT9NBHSQOxnmiXb8Muz5+YQqKxvdWipUM7l3J02OXifI+8bNMJI2N1//Rrx42MHfAEP6Z2ic6PqZ30ID+mttw3+RF7kbk7i7uU8inh1PmEpsmFEy03bHGWpFOTRzApmiPz/5A0VOPks7+l9jALJyCHxU7S/SG+//x7J9lO6c7G02J81YhP+lovlZC4xVjiFFfIm9z/RXIFDhf7L5lTFM6C5r56tQrGtBrQM5r/9LFzZ1O/9isY17tgXL8K24IDnE4X5UXgT7qqlPknsrtf89NV6dra7RmxFcut1oH9acUYVn7gLPvLex+zpzHked0ZGPKpcX+OlBzEQvOuxb7VZlpLChofpvBiaJx1dM6YcRftLv4MVcPnoFVMldFaK/lj2R3yow/MY9M8OKAuSBW9jj0EhOIRaCu4G2EfWPo8jb/7ez/B7U9w21yN2xf4diVu1/MtpMqlL/LtEty+xLdwf1wKoORugvw+1sbw0d0I7yLh0ac672asBq1xxuQ57sYWG/t6/gfeNiOjaAFwiS+1Ozp9x6Jh0fHkAINYnKDiz0EVKxlUi2jGawdngtPyPyVK2byhoxnetLETjVXYVGksmRDkUTdB5vOcWZ6xCsAv9iK734bmO0cayGxGnd3wJYn++2+tiN/q4+4+/JfEG6Uo5ruLSrPoz5LCUqyLJXNLc/BneM6xz4muTdofmCV4sYtSrJbNedm8zUezy9oRLA5gA533BW+P03+qdDYsy0bpWkG8Gbu6SQV999rdjVcq/0Ny3GMcozitJSNqnGJ2Ns2/j8FQFNplczlqUApPq/RxGMmoXzQPxdPuZzytJL1hzp7j42x1OzOkam0jzPi4UN9LfCYrfpfy8oBwMrCdZqjJhEdIlEJ5InKLeQimiNHSc/zJc/yDbHL9Pv9SDe+CxuCEQyysR5+iCpP4snkIpkq77r+XtvHU0sbF+BC0P48yIznPQ24ZSPyEBvOa4Ull2Z/avNOHbF52Aoxj0t3YjkUDm1rtUErQb1J8Y+Ps/TSg/B4Zj8FRtM7ZlAqCV3Nq95rQS9d6CaLr2lFds8S+MTSOVpA2QsQYe/IfTYyKJbO0YSK2m5+TiLLCjo92M51qzssFw2E+sLsqaMxYNINGy2LDLDRpVdUq472GbTjyg4iwp/DudQczAEisd8opHqaA46tOv4tOs9Nhpj/iftd6dIJaMPinzJb7laReabDsE37X28ehKINq49OhqkId9r0ZHa7P63W8rc87mrhTxIAH+vrq58KX0lb4UapAn2eb8n+rJI8qab9VEg1dUpXUh5KSiTEidkiV5IRrqa3sSTXOYRRCpmXXKkyIycTscWfBCBGolLvxY+4eVp/IhSgmBoxMdBYLIAXFflds6wmilLLEVlHKtiMFeowxNz/MoDuJ5nLs9HXW54YLjPcd7eqb0nbaz0X6/F31V4nKLkW7xbb2rtcr6Tg7qtIAXysLWFoTwGxgUWIecTDhoG5w2+LRQ+CmQCaIPJzF8vCOLIfSWfiGDbu4Cox/idHDUpIZZTgi3wvIvjzEonA3cQgpTqaIF3cj4L93MzTe3I1P8XI/GrAUFLCnRQwHixBQg4O1dWUyfD2O5sqk4rTQEKKCR7kCbYoqCg4CjspbS/Nst9N4RMfAW84s88m9sgHAPC1jvI2y0hlM5/A819a/eUa8hUjudBpmrm6YVns3A9ZoV8ipvzlmejqCfk8TonTOrsMJkTjTuxn4V2SMdKbSgB2jz67DQb7LPMif+1HGQb6yyzrImRtpFGDMCP7lJo3iHQNdE5gvM0cNGDymRyb7TlD/0pByDaUM0naszWwwwZnuJ+021mV//IRhLPSuxfKL5OtrGQPnpwV3GOcDViy4Q2FZciqRnCZIjVTF2oB4G1pFSOlRNRmRkbGHsxHFZa9cs9liGAHFoIUReVupM5yzOflfjIJY/5Kx85B5gCJm0wUm4huZxFQoEKOXKXG4CAG4bB6oN7wyCwBzWy2UDVp7gKW+P5q1wOi4QVvdjeXADRxqQYjO56dvLPQoZ66d8aZBmECE79RbcFAZMySD+FZqbfjOuH9NKCBvP5pr+34Tgmqs8P9CcHqO4bCmtvFLRCD6NwZ2+H+VQ4fAO3TkxOOHYVBgb00aRGSK0i1UUHwtFOzELvnw7yCTXkOHA9x4nfE7qG+p9MnfwWRDaRA0JWHqsBWLH5Hp403zDTYo6YV5Q8F2KtB4BUnMrL+nrBk94tTq1K0vjEXX2KI5hn9NwmFUrsGTuylC3+OsYNrhXwdSWcrXU81SH2Td66aVl6rikdeSRsIrP/rtgKF4W5ELRTO2qq/jYY66FK9Q9uyx9myCPQSbdG5AIkeOihKevstzekWxeawodkCfJ5veca+AdpNvNQ56d7wTmN1mULM0e7/hDQ5egAKCTTvdLc9wYsWeehzfFbNn+qrYDstvL45J5vZdKvy9vhjyRwsUYFPntbsxhJzzZPVcKBkus9t6sFC8m5hDc5t3E3NobvZuAl6nXS+Yvybm9fr2RUcW77OvBiHd8wmqZXas8B/17XC3wMJHJIuP+465Hx2gj8U77DFOuR0pK3t93Ic6N51OPu6UW8UWF2BzFAswPs7RDhePnElTSsf5DU3vLC0RfQj6514J4ZTwH7b4cs/gMVcsLSxe6ontyC4+Zo9Kw3/YO+9w/d7YC6jUFnsBJJ6t6Z36CsFDUMy98Ppl/ZViM74RKjbfZJkFrFFsFeWFxeWe4q2q6Rf55RydE/uO17Uq+AwkIA3Q02wiy6c6EKQ8+duN0PtJwbL2dzPOeBZyHpEnf3EMCk/svtkCWX+zE/Q4O1AL2YTs/Q07lqscDDCjP83LX2+sBnXBuJJJPzPVJn+BIh8oEl1WeT9AeSVmeU9zeQEGuCGTxcq6PymnMIxEAhI1g/yD2oDyhgCvApjvIHw/JsV8p3DSOQPvAwhI4WW+S2Skl/kdKlB9Vkm7N1roblrJuS0MOiPsnq8rcr/JlM7xRge1eyAJV3xkj8lHdio+csRN3yPDBTOCiv2einB+SrMH3mcLjhIw/S9ZuejxotLjqJxor3QmRoXzQ/hn5grbcQdgHFSgmKbCG026m8YRrLgDjp8LbfLjXzGCrahHmDBXYa8sKHI34kT1rsVmdTdezfcMdZugyh7yruUWlXrXcotmeNfybrqEBmYt1pai9t3Ptgfk3NKk4V2LsdCWCWaE+prBoErcrRJ512KVasOCcgqlDCbmowysSs4=
*/