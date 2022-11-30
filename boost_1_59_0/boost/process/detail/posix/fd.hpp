// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_FD_HPP
#define BOOST_PROCESS_DETAIL_POSIX_FD_HPP

#include <boost/process/detail/posix/handler.hpp>
#include <unistd.h>
#include <boost/process/detail/used_handles.hpp>
#include <array>

namespace boost { namespace process { namespace detail { namespace posix {


struct close_fd_ : handler_base_ext, ::boost::process::detail::uses_handles
{
    close_fd_(int fd) : fd_(fd) {}

    template <class PosixExecutor>
    void on_exec_setup(PosixExecutor& e) const
    {
        if (::close(fd_) == -1)
            e.set_error(::boost::process::detail::get_last_error(), "close() failed");
    }

    int get_used_handles() {return fd_;}


private:
    int fd_;
};

template <class Range>
struct close_fds_ : handler_base_ext, ::boost::process::detail::uses_handles
{
public:
    close_fds_(const Range &fds) : fds_(fds) {}

    template <class PosixExecutor>
    void on_exec_setup(PosixExecutor& e) const
    {
        for (auto & fd_ : fds_)
            if (::close(fd_) == -1)
            {
                 e.set_error(::boost::process::detail::get_last_error(), "close() failed");
                 break;
            }
    }

    Range& get_used_handles() {return fds_;}

private:
    Range fds_;
};



template <class FileDescriptor>
struct bind_fd_ : handler_base_ext, ::boost::process::detail::uses_handles
{
public:
    bind_fd_(int id, const FileDescriptor &fd) : id_(id), fd_(fd) {}

    template <class PosixExecutor>
    void on_exec_setup(PosixExecutor& e) const
    {
        if (::dup2(fd_, id_) == -1)
             e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
    }

    std::array<int, 2> get_used_handles() {return {id_, fd_};}


private:
    int id_;
    FileDescriptor fd_;
};


struct fd_
{
    constexpr fd_() {};
    close_fd_ close(int _fd) const {return close_fd_(_fd);}
    close_fds_<std::vector<int>> close(const std::initializer_list<int> & vec) const {return std::vector<int>(vec);}
    template<typename Range>
    close_fds_<Range> close(const Range & r) const {return r;}

    template <class FileDescriptor>
    bind_fd_<FileDescriptor> bind(int id, const FileDescriptor & fd) const {return {id, fd};}

};


}}}}

#endif

/* fd.hpp
w+DehHTV17bKOlnPp3b9OBPXWt9T22lCNv2SnGMpj/99zyMy8Y/DFKUQgK3MKZmnEYJzL/BtnelTYCNBWw8hZACH+s+6jthxkXeaVeV0UuJf0agd/HecP92sKvduiH3j+8QdlVBTmsSPk+wjnvl9hA5GOnI3UFSouHqNNFzX43PLSjJAW2wCN7okygZb+ggOVsztzAs9Vnk3gCK6Yn352kHrLaXiNamcFPa4siD8RXvMXvzZNizgipExXuiGkLwYZywrlv1jHwNGYiOhwSUq/cr4fwA4gMd/Nxa0qeB43kuYm0Xo64giGB1UmXsD4rHluE2/BNX4RRBW76Es9I4rsxuIAHzxwrEO4rw3alNhQTdhKL322MX4Sg/R//suJkYctiZfJseKcPTZi79EmouqctbbyYuJ2yz8pdnmI9CmGNZx2wDo4chW+BAVyE2kV8wixTlantPL0f4Lg+v5+AJ6kxBIUwZ5eOBY8Yk67OxObRfUeq7Huzy1Vff1reanXoKn1GFP3jaAOKPSA0Q87L5Vn8R4HrX40mNuJhMKHBldMwB8/FhPGQBkIzOQLIxteLfJKF3M7mJcO4a2sQeZdhsFLHPTyOwy+jl63u8YywfKzKXGCdIeusBTaU00M9xTod/c6GA2Xv453imK+MD7uQueAqJcUnAD5UDo97jW26I991+TAw4Nxnbf+Pq4jjE6BP+k/ePbTr3ZgWO3D8jRIzazjiY4HAWxkn+xIJbN/uot3ZJPZu5terNdN+INml5r19lPKA8zFf1EWhKya0dxpxm3OKDOQm3Jr3aa2pIVtBvu114aZ3qFS6WakcwUx5rA1Tk3yhLKTrnxunad/L+012/oJJeKB+AT1QiY89PDEZGj4ZLmH3uOXA/7ZndPKnH3iIzKMjQwCA8ruAZ71pWNt5jxGhna8BWtbNPCOGAz5GL0EEz4himqCDjFJ3bSht3GwCPZ2qFlP+mLfBgUSD2efr2h8c7Wbld+0ivnY4MXRRucH9vg35f30GDlRT01aKUGgzO1X8e313wdtQc3/vssNFeOzb2VHWmuPLa5cT01d0uPzSVQc2GUEbQzr8a1+BS3yPfmQKOLMCuFR3xCVOyxfdKFbaxFZJMEFv77bWD3cPY0YcTloJidRqjLZBtVNgFTX6eVvtWqx9k8Y2Mn3kApAsnPGq+kY/FR2I9ui5CeiT26h9yqL+6HgRxw/IUpw3WV9thROmOLG5XiegtG/9SZ+p1sUvi2KA/MsygPlMLfAvh7zsIRQegfse16dHqzP3H5AOMiZmia4ULkcNIpSQs7OTWo/3JWnk6RjnfL1rpzcBt6Tz0HR0wpnKmejy6xoCv0/ab/vcCqhFn7uFF4tL3KuujgArjuTd9Gpb04dVgJF7yACs6gan3pDUKhR8KyVeQtSK/XY57h8t+k9VQx9MuXXtO17Po0B/vJ79ae6X9cF0v4qU2ekw0nv2DtkZ6J1dmXjRxggS2fR2e31noW2cx+8+FqNM9btvaIRFNgREld0Z8yMscN0huDMCWvUOhw0etgVOaQU8HtGNi8WxvZC3uBB4i+CUrNYUOx9gjlIMOZyrqB9+Qdi00m/573gcmf0thmaooWyXbKqVGQBPM1CkHXDYw5jMCKhFsln4E9VDlrfQbk7PORSCj6CPb+tMx2F/nOzL2Y4Xu8RojRdm1ZE5DmFsOz5ms5LNgn6rtrWf2LAJWSU8GLpBzWUQ3qW4Q8oqLZVd8LShX8XwZ01nck0dkinoQfr8cRHnbLCDyNYUFrGU+f0KMVsZKOg6XCJvQBaucQsVUbeMM5Ns3lD/Z0PGZhhieoJUss4eNxOx+PkvMto7nHVoiUQX91Wk5+QTj6wRV6yplrcHUMN0AEPPrUmQasTxKK5qjYjOopd7OechGX+BkJ1PQIevca8lq6XLvx9/TWpeZbw3Q5SCQ3X3hxPaWYZLFlEk7I04dIAzpOKIPJTOtS8KUKrjbUm741lAQNxj9dQblC9X0Ag7/wFzT4a3jwC69zMMLubq24L5LrcI4Xg7fMRTt+FaJEkmqQCPzh4620Q1dpu48wBH2G9qMD94IwbU+wLbb/09gWrZGombgMuhQ7cc1ItAOF7ZdcZsRld7dazDGsFtld9WkY//CJuSnOpFns1Ob8B22U3+Fx/CAtmnI6z8MV+MEpBdHOfwHGjY4+i1ncL0OfFTpKNm+Cl6KgFaIyCmfMsxrPajf/p50VCpSN2K/sBt6j1jgeauPmNBBeu4ISvAJDHHT92hGCW8vRTa95oAGOncXAwyQUA2/x6IgMkG8uBZ6GPDQ5ptpdXeAM5zijeYjQQxp+oLsgfI7pHwFijj5jqwvn9KInAiPGkHakxvA743d4ZRQ6b1e8BLyftmtLBwzncmTTA653V1yA8bcrDV8pzZ5JTuHbeqN79ww4IpdiAbp1z3hd96rvDCac/neQt6ktW2cxgWv+VcfwdGkYNXv5BwTXRo92SSYZUKlJY36CJAvVR6ZpAblhLc9A/FeRAzNeHmn+BuiZT/yE05SB6FKu1azdDlgpVlNacBMaddyrWSbLsEZkslvE0EblaRneshdpVSel6ik3XsXwkicInmypDRgEM3FnKnRgkoOEtMCIXC2xHnkC7i2nqUPNUmx/MfzYoKyT73TCEKXBZDNfx+ygV3QgSTj9lIwcaQJtSc3XxhR7g0iW4kDcpvhiGmVGexSd0nVMc2i3kkpvQZ3FYkqSyBv31hJWdxiprSlZBk/0TTbojSgakeHRa72U6Yre6Ncf/IS6XL++2et+l5XqH8ESa+6lJQ8goSp+5SAAVhz7XtHC+rar8CAKzzQsIZZ/8KqfkxC76ru4B6ONEjW8d/ZiF9JzOcIbsAzC/m11xH8R5TzRGXA9lS2VNtsxDK0S9zSp9BDG5T6+X4dl+WUgv0WdQQnOVSLH8hU2HkQp4Cqk9VhB6/F8Wo95dTHL0dEmOfud+hvudsE64duBq2s9+sJDh72bvK6bzg43fO/tx4YbvvfVD0pXVVcmQ6HfJ4QGtkl32a95G73Zp9nv+96BXu114aFW6JDhj2CGSj8+HDGut1wdcUcwHHLg4ntXm0hyeY0BtRj/ND0l/UoHp+cIBxtBeE9farApesp96SYOpJHIhMRO5vgoHzfm0Cz9J2q5KwL0UAWNmhMqcu+QvHWSs9pdp9I9aTK89zGsA49CT3q1ajxCLmfpviM54eTe6TWoRasoJCc0KbDF465Sy9FF2SsFqoT9P685LeGBnrDH5pPerbOlvHcxHOq27Wp5IR9r5Xi8eUdVLIo4qKlLcY0oVR3qUpSeVfJXU8vxUG72ABUyj2EdjZt1BR+ZJ4AjNFgXAyyXWZfhUAJfH2RG1Lf44Bl4/ZBDLMeGmm1ixhF8bGD8Y1LZ35C4xdGg2OJ1beRdZSntKrq04BsMJ3Zv5F1lf1QVhsN9C4afhe9AdViCPiFNvWcE6+/CyTb11itgLNN9Ve6GopQgAuTIYhvsO6PwNe4AMWGLMle2FPSnqyPgatMZ8h3kwz0ETxT8xlQPNrJ6sLFghuRM4BZMfdWoCWleMQHR2X31wtcA/O4+4Ly97tXEBwzgBB2kqcQQj+Y+Iu+goav0pO9B23DmXgqN7HNLm24+NQcVorO93BAFXt4+wuoJJw72hydb1XKcpOYrUaf5iKlmvM8Yk4AYWBcs2xua5FF+L1tCNo9erW+S9Wr3UuIYt4sZx4Aqqj3pDXpNOEc3JrmXbTm25NE3+zH4jrb14oEwQk1Pw7ak/S4Z9T2P439RUEe6LBql0K3YT394gu6icSq4mXtsgoOOotq9aDQn9V4Km8bTzPfXqz16lfH6ff2o5jvqFycjBNDHatis3ibV9VomgOXRYyXzQECMbfG47pVZU+MXd8IG22/aO8CN1+xjbvyXpt02N4kigJ9YxX6xK/dFFB03iApSFxHhqguS0y1xuiiVMkApG8lnDQFRMtINQBQqxLomWNSzIk8YiidBH7F6Tb+YnGG87xAZ9dQ6ApKe51U3YJ3NvbV+fVlZCDMh61uMmZCea4dZ8LqK6xiAmnLyvmZhUESQVyaS7xUeFZl7tUET432vom5W/rQefK/GpDmMLMi/Gs1STXsp0CHdR48cLOOkMuxVvewtPmPmWX7mjNEm9KFTjDLj2CMwo3WX02Ygld5KjkzU4/VoOdV+NaFNF8EqpBsgGyCdRuBA2O27iLDpIyPoTd8KqyvyuqTTY9cRHIrrf9T1pilQ+w5RsoOyxUXiGGVMmfdGBKwTnfXRmJEgqxhGuIl9dzbJ4jYngnmIuqbLetss6Dvwv2yACDrLjjmZ7bKOif6khRfjDjT3e2/4wfOIgB1EwP+kTSt8mjpR1kKr9YoW7d+j4m2v9T25BeSGJ56ndPQu7ucNTzwfOOeGSQ5Ls6R0nFd8AUHopEwd2tfCzMWFR1v15hsV/aLi69ZNPrb51pM/VJ+yGcCfYtPsqoswUC69zqNU3wdSMyyYlKTIs//5plXHrKS+COzbp5iYNDeNdDLntMruQIS+LdBFOR/O8zJSw8NQuOuk586cjRpoK6ahgXaUg4jj53DHuviyJhC+3DZZtDFK4g31SOOfmSiJDRGUxHsx1UxAnQ4fd+Ri5sBkdB8C0cPK4aA2CjSgra7SyFigcTIYrypYt7MUO+9P36P9IwOhBXd3dbdt/smM2R8wBOSmaJzKNqvVklkFjPt9Q9DtWtEomJyzENUE1CEmzveUbHzHpuE2q6WnGM9yoBWveJWzZS3XCGS9xfB6yFDLW4yQ23jMOll4ZFJLrbMYMbO5c1AolcVUWVbWIw6KxQTavQKOXppeTBEETGB7Oa4eK0aXT5U960zlhO1WE0QxIz7WYIpMT//BbIkqIa1adCx+e7XVoqxsoFzQ4WFrhvWNHwOqx8BZ7xaDYIyD7qVxaDCAEzJgMBqsPb/7flmpzqDsAt9cQoL8YO3xR9DxDFP8gATPkntGolFTxFcvmpMUntdT3rzESLxXZXRTTEK8DquZDZSuyvrMwijOMWECRHJ0Ui35XEtvZTUlKmqeSloIsXwVkdtkKFHyCwcwV/jb3RAC2XIiTN0Ch92E5L7qNVwwcMliXLJr5485E7GoZCRYLF2Bi5ke3xtMfp1GXluEkL/6Q2dMDqWSWYZfPOJbmzDtJy7l7sphBYGmmq+QnKTck8nPLLbktmjJwTbTO9NAbZ//ut2ATJDDJY4kCoCdYyecMg509czCrRa2WZr7sH3G8L54eqlW2TXFEboI/jvn9gVGJX+T7PY4i36Uhd+hvZFAcVVpPflUf6DH+FQ/k9CjT7XThNK//J/RcZDDT2VwcICesnY4kcs4yQljmyOvp6Bo8RINfJhQPDaZb180PCa7TkyiqROpMeD1z6yyG+D1Edz62D4PvtlqifR5u7XnPudFI8fmfBATOVaCFAKTyJOzX1ZLCO5VLUGuXrnp8HmcpdLXyPLRDvjdjPKU/W9/QjHoLnvCxX1hQZV0JGKuxyr422wxY15BSqrvGs0FUzd3gOT0EGNbBYezbRsKZTkZ6TlpHluVW3FCf4qhRE6E9U3fpPrqgSmvAtEGwfTqMZ0YEh18kuIZ5IGLiYiuYBSLG+hXAbpJ85jnNfLQGllS9JQXh0dZj0tW2qOpLmf04A8cEV9ZdvWKVSMaSErXDar0uj5i8K9wJVJnEE5uydcREG1e90OOoqTMqqavia2BZu6dhSCUiH8m3h7xAX604NOIDRK61iOykzEeEcTTdGClsxPJdRSBk7IdHkne7Um3gIxmAKfU2lpsTcK+sv8Ai7sc+xMaRnybSj+0Qa906BGNcB/4gRQ209Qf7daeWNOhB8UM9Kvx6FPnbAFWQEdNgoz/svFfFpK1V+z0IvYL6tENi+/9wGV+stuoEKt6e0kH20DiGbjZ2SaojmmtY/uIyfnEYn/GoI6LVvEmEtO6awkjGujFK3mr4MxNEp8Ai9ZsHx/22i0qEZxX1CE8hiR/DhSIhONN92R4bZ40r3tTUW+vqMKHoRkuHRBvIjmQVRIxOee0temLohhnbD7um8rs6uEThhIeS97cTkw9YiIZsJ8eRgMklQyWGEoldmmLKM/fQlxU0YytmH4P58af3ewAETGNWxowzGFx/x07li29WMvVeKBLotZ0HUv1k8kJ3ccOmz5M7m2hqV0OtducpL2CneAWOp6mAzMz1YE6YPQtHoLNX4JMy1BgeNDvGE6c6kS/vr3gh5hdQvv2bKsetx+ON1Izn6x/w4p5uKc4cbJn/6dNbx4EXJP2zqE2nRvejoLPpWcSYIRzjLZjI5wOTjmh4/4cyN9UtrfwwoC7JBfXuBPzcNtRiZdYRdux9hB1ITbfXAx+AmLjfPhuBD8BtxCgFaTnbbKa10DJJLzigRavKIbPPBAUZ5zwKLWJHmWTzaM0J3rC3hFnPOm1PgH0kNfonk/0os6ol16r9qbPx3kgdJpAfqvs+hh7KC1MsnJynAUEsuXmq+EhHF5LthgxlBSA5wkFURVrc5JJF1qn5shyPvBI6Cf1DTmULGHUxf2McEOoi5MIdVGFbqt5x8KJsPJmnPCLPbALBsKYAWM7bdA2xlz0iumFnvBEeJ2aBCi4z+VrmdsH36nD5dOKhnNqnQ8HGwAXeQ1GFZhL0cJ66ySjd8Su5jUwPD9xqcEGEI32waA1wqDVm6jetbJ7Pr3wc52otTeAAo7/ia3xK5hhzI01xWt/PYOM+IozNI3nigHHSEvZ9R5WPdeLbqv3ggxOFHEHyN/GqLagDWT4CkpsidFbSGgghT780AmdfVXRB7Ycnyr6SJk8OCaMVanAidVj2BhN4g6dM79B5gGYdoTB6vyYMjK5XqbOXY8w4rfK7uXUOZ/RObKoJDdol86FVqArNeFQr4SY7myLDbeE/RRNbEZXPHfXaMrpLn3hSEs1l/k96Eo7jQ934RbswjizC9dHxucKTM46R08JX8iMKcbF18j5W4xOFJ9H3GEzCJyfNDs0Cds0me4eY0u6xcSaWE44X77MI4Q1vd+ctd+Q8Mmo8+/zmnie6Zp7N7ZFecZpCQ0JuH8IoTqWziWGFKP0pbL4AW5hSt4k84iKucs6Cn/+Ztmt0IguhnPc4GMLkswznbwDvxnkiMKfTSPE40f5xQzU+ZRTaCmMl/uU+xwWhiKIvBBmESy8EbMj4uBdA23wiyR3akPKYJoRdYBGlzu0p2v0ovZOZ2w7cfz7fq0KaDbT9NMcaeqNZlojKUS2a39Cb3b3FlnyngXmrXl05MY+Qh6tMzw84WJtjoOHzGKmb+3Os5u8eqry54OE0Pznj2zsYKCV/sTJfi5Q8h0WI2VqlpFdNj7/RM/YXkifsfDjJqGORULNNQl1okGoDA2Oy4Usj1bWlHQh1qLN584akNdBlt4e1q2JP4IdCoqvfOil3Ba3cgg3A3o1y+zVvUavgmIHeYkkN3iAr0HbIHVtDSPeXdu1exsiOotHzfRRsK5nRSE5algA/kJbfTJyfnXHAqDcE8ANlO3FgMdMPfM7rzoPRWSKzJJdldTt65ASf2VS4l3GkkL2K7mDeonZIwjLjLYcpsftxqLQDj3XxkyfqcLoHtvv11cgJp12uv2cfaW1jg7lNwWEWONAHItg2VZcJFulBcTfubcWPw1de8PBfqMu4oVC
*/