#ifndef BOOST_SERIALIZATION_ACCESS_HPP
#define BOOST_SERIALIZATION_ACCESS_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// access.hpp: interface for serialization system.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

namespace boost {

namespace archive {
namespace detail {
    template<class Archive, class T>
    class iserializer;
    template<class Archive, class T>
    class oserializer;
} // namespace detail
} // namespace archive

namespace serialization {

// forward declarations
template<class Archive, class T>
inline void serialize_adl(Archive &, T &, const unsigned int);
namespace detail {
    template<class Archive, class T>
    struct member_saver;
    template<class Archive, class T>
    struct member_loader;
} // namespace detail

// use an "accessor class so that we can use:
// "friend class boost::serialization::access;"
// in any serialized class to permit clean, safe access to private class members
// by the serialization system

class access {
public:
    // grant access to "real" serialization defaults
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    template<class Archive, class T>
    friend struct detail::member_saver;
    template<class Archive, class T>
    friend struct detail::member_loader;
    template<class Archive, class T>
    friend class archive::detail::iserializer;
    template<class Archive, class T>
    friend class archive::detail::oserializer;
    template<class Archive, class T>
    friend inline void serialize(
        Archive & ar,
        T & t,
        const unsigned int file_version
    );
    template<class Archive, class T>
    friend inline void save_construct_data(
        Archive & ar,
        const T * t,
        const unsigned int file_version
    );
    template<class Archive, class T>
    friend inline void load_construct_data(
        Archive & ar,
        T * t,
        const unsigned int file_version
    );
#endif

    // pass calls to users's class implementation
    template<class Archive, class T>
    static void member_save(
        Archive & ar,
        //const T & t,
        T & t,
        const unsigned int file_version
    ){
        t.save(ar, file_version);
    }
    template<class Archive, class T>
    static void member_load(
        Archive & ar,
        T & t,
        const unsigned int file_version
    ){
        t.load(ar, file_version);
    }
    template<class Archive, class T>
    static void serialize(
        Archive & ar,
        T & t,
        const unsigned int file_version
    ){
        // note: if you get a compile time error here with a
        // message something like:
        // cannot convert parameter 1 from <file type 1> to <file type 2 &>
        // a likely possible cause is that the class T contains a
        // serialize function - but that serialize function isn't
        // a template and corresponds to a file type different than
        // the class Archive.  To resolve this, don't include an
        // archive type other than that for which the serialization
        // function is defined!!!
        t.serialize(ar, file_version);
    }
    template<class T>
    static void destroy( const T * t) // const appropriate here?
    {
        // the const business is an MSVC 6.0 hack that should be
        // benign on everything else
        delete const_cast<T *>(t);
    }
    template<class T>
    static void construct(T * t){
        // default is inplace invocation of default constructor
        // Note the :: before the placement new. Required if the
        // class doesn't have a class-specific placement new defined.
        ::new(t)T;
    }
    template<class T, class U>
    static T & cast_reference(U & u){
        return static_cast<T &>(u);
    }
    template<class T, class U>
    static T * cast_pointer(U * u){
        return static_cast<T *>(u);
    }
};

} // namespace serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_ACCESS_HPP

/* access.hpp
SiEe0hQ2Rcta3AmOZvMwk+QEcBgncCEp/dIKPPlqkgZuOk0rwdOFiLWbwa8mVxxlN2mFpt2VRxhZGQ90SxA+gx8xvc9uXmCHDCMBnwlcOREW04zKlexuJg3+po5tjoynoHQR0H/Vx/gfhMHFovmmDOE7/uxcuUDwJOJwSDa69W1LQSy4lXkmR6HMEO533MRvslnLJUuKA2ZENfrhM0xXMDzAUIWxNF4r0YksJWuPfQ0H8x+p5radHuLI23b9GuJZeJDZdWwjnrgydcT6c45TEHOo/wEmSr7xW7t1mp6KV06qGTwb8Th1JXFQG4SMLt1sdo27HiTsl6PVFacdWl1Jec4gAaQWT4JtckTy19RKl15ho6/19PV8euqmnH1mrWMVr4gWTr4nP9m3xl/R/ah/EzvrdoW7qSvQNaNTFuNIdK9SZvr1X6QFLeYSQsjNZTsfoN9dMDVNF6LYh9Mg+0dYeMC1fKlABk983H723KLHD9KeayUcjGPQ1ZJcpF4XyhIVj0znY5s34o9azzYFN7MIka3p4e5zwpPKNQBhsM83vrTP9/GyztYzfT5D0v8AQc3ptUQSzwmKHRc+IRTfzHdwPjaXutA7DAPVC7Ob6HRzOX15CKilpS49z1w4eBxe6VwOhKEv/JjXlWmIY71QgBEXTjXfI8+1nvFyhNQLqLS8e7oWdSed3zlj03JZgj81ttG2qKJ7aA9kyN126GKK0/nFp6g7uRH7KthhBOtNEmGMMeKTlBbSl1CkH1qXVUitxTaGykluV52t4mD8QMnjLmtVN7mU9TvZGrd1POkbEfX42UE3a/gMGkcqDO8fk75huSNOJbiOx0uT0XEh0n7cJSdgG2ioxRXd1VGXoWbkb3XjCRm/foN4aXwI97/VBayxWfZ4qVra3Jw94kEqwizLpTjwDBF2DbwUmqmWLdfIRCo6kkCFEEAQwcs8l9ln19BSPiMz+pLrIRCjQzsD/HRgiXks4LZNCG3fjQjJA6QYbfKeHOxAo/Il6uIupd3chkblZqziDoSdMA99qN2U5e7qxA1R/ZNAfyKX/kNckuCLpn3X45ScvGU0vA5XPa9qGe2W0fQlZ21zruW4teF5W/Gu59yYfpfKnWvbie6ouW07f82FUQWnN6qF3PkcGnbawfPFxmL2VWwzpxCohB8y9SITPiZUxbEc1pnkOgxC+lwt6kofPCs5ywFwYIKEHh5FGqHiYfNbf/wtnuPImZXp6bw2yhwJg4gOmzJMRwpcM9XY2z+sccA3geeMS7tyrMFWqjhjm2yLjBW4FvxdfMBIHzZP3UcKTMF3e1fe4zZlCvGnhIek9PmPOzlgR2Da2CF5X3f8uKtHdyR9G/eBlwouTSUGM7wDCm/FDrh2CY4bEGvPDb5Pe6Dfr58OgzKn1V+1A1k7dwzSCNQZlCTKmoPG87kbdKMO43JWFStzgkjnwf48jNWGb1rdz2zjkYvKlHmiDngQGl5pXvjKIo7yJtl0sYpbhMq1qO4osaktQtTLjoc1dWPSVyUK4T0MztbvW1QjQdq9uA77tbUmGa1P+hqT6jI67n2LqNONYLfU8BCesYrUp3zHqMFZv+HnqjI8o8c+xvqfQxPe7ztWz5W5sPnbkjDyNZUpvafxHCxQqHkPdoxP78Oh7BdehIYf2i7uF1Qe8csqjwFB13DGgFH02HT0qJSvhYjR95o9MddRoVWjSRlwQJ95wjAeBRlIS/LMAF4Mjh8/k/4q0WBjkl1ZT0j4VmZAJ3l2/v5SQBVkFSHaR6fzBaDXUNupOfCOUMvPNoIYy/74K0t5Gll0NgLOMbgUU1mSpU1747UDETqlFb71CoVr5uLgAjbC5YIqh/cSMPWbYb5HZXqtJw8fm8OsbfhB/O5CDXAhy4GXRGADBw6JwEoOvCYC9RwYFIFFHDgmAiUcOC4CLg6c4MAuPYKzZU3dWmGqvxke2XWZ9o/cgQNVPCx/ZaOcSEFD2Ofy5uAElhNb7ODhc07wMpU7vmap8JrS16E1yN7qihCB9OR9FmlXiSv7lhZjoxLIch4bxWU8EUG4fT8cHpsGy/EjAqH7Uk2DuO4SmlODWiUUpep2Hcdh6TsWxm9dYNcJUHSHNd/xxl0DeDTGdyKM38bArpe+hhTIMBbTqlDlatWl5LOrG9aeE7eWOcp0bt3bp7iCfqFKAfcXO8Bn+jqFNgEeQtMqufpa1FpeicbLa9E2ODjQWW6/vrULmsZ9SX56183klVaAnMmmQXlPN96UOb4TZZK+YztRT9J3Qt6dgxfgWJ962dyzuFjfiMnCUlm8C0zIyI3IgHi6W6s8Dl/DkrRVAnHLvpYpacSDAsSpZ8p9w/Ax7GZnyo4cNMxPCxNUI/BqPF7u0800dBL1PgX3wWZNh82quUaCb0odTEUHflD3gx9wrT9I+gZ2DvAgDgkHJANUJzeaO6nFv99OxGkUtdNvvBbTI6lzjaZBzXeozmg6ZvhORGQCFl4JHET+AVxcWLOBZ+RMuYpH0urLXPwyRDCk3NVIyFgpK4wTBdRe5lbc8TN2hRjGoek47s/YVTmk+98wFy28M2gFeFmhorvKJpQD+F0Aoj5SzgTIVxCpB6jlnYiGYsMUqkS4TYZ9Cr/dgAcCYRwdwCPEz1t+CYRGIhb7BiL/6Ey2vAdZ6z5ip1ioOpsPPRwRbWu1IG7DOjNPFHeC4sJ/sUKTnoGwKqoLp0V4YigRSX4wOwJuhZc7lHuC+ov1zESv4pcFrHcFPAEimredxnUiYaK9lDkkfwMKwttOJ+jfO+/UehuVG+J6rnJJXM9R1sd1otnw7F689inwIkqBcP4RKRz6tk1cvhQKfZXFiXWgSYqezRKx1KaZWTyAsJe7JiR3YF6x/7S+9Gs7T2A4hrdfuaW69llaZmpr/LRbFFXL+fGMw6CtQyGxT+CgPWxzEhfAYVTdjQuuiznroXRc690P/4bl/eJiBQOpuRS+CZSixkZluqhZ1DsUYCrQc9YYVFdA/wpr3HiGoFtivikCpdypIrv5kH2mYgyaQwUG7OgRi+fs22pL31NmtNVKI4qbvkeU3LbaRSN0EKDLIhvetG/wnmx/YeiVMzAo82w7swhvZXf0UnDbmVL+3sPf/IZ2x4/5ex19w0mh0D3lpf1PZ0xpjomPaWxB8fIGoD2kUjLN+97izZKkv/sS++oowzu9Gf2be4mgqDi4BNpWyaZMdWuGfTwTB0TYP9k0GlDOA8PKDOriRCdeO1bLjCKcOumiSN7ZKUUlHvDPcgKuhKpbiVn9d15hRHieySUSrVhVuQHCHQn9Gyx1GKbNrhLDPAJVB0MdV6jPOAahcV7PtalL4tHhPNULHbmMfVNFqiMHZatWnlEvbqwqVi/U1JIgfOnoP/glzqyRVH0urPOg+PccchIr6yuhdmlzL37mkZuZLfWYTZ0wmyrlptaugRuRUcprJr9kJvs97GBJOae6tVSZLnbiU/B6rP/jUegO+0YtZg0aAAgs99OmpmxK7nhG4A1cmLIvlQrTckQEwWfsusswWNgSjAiMxEeLyE0/4oJiHasm6bewZH9BoluVzSR9+vOQ5Wdw1+pRpnszW+rDy+eCz4BcO31Vtc+t5HkzKnsl9UecZrGII+sFBlUvjdiTzyFBH2QetBQk+GRriKC8b1GowkiMbTknhKfK8acf+DXjlaXeM+1/WbumV1CjBY/SxukqwvC3DWMlBlYQfsFDKqHIvIp3qi8FR7f2lxhoW38OWJgqadcBsCn9OQP0c56zLVn7AsLJ2S9thL+nQ/i38jX6t7NokP5VGnatb4dH+ed3xcBb8aLPAde0DFRqTrgdtRDVW7sBHNXsjfi3YDP+rWxv53ukXQ+iIF5ETzXOT/J7GFpjTrIAd7ta45RkwWs49jcWeD9UFkUc+m8XG4Z3pEWZuyL8SCmhnJWlODGFN56ngcvOrBz6P7ho5jfWG6cnCwbx3F9jUbIAPpq1xnOTBU9zzOxkwQn+uCBZ4AegXLE35M4CSErGpFI1N3lp4zqgwKVjUp2Sm6wd34iEGD4PEdwidfqDtFuFx6cW8ZjNru04X43D+kefNTXutAJmQeG4eNcjGCg6kejd9RgDAmymkl8ARRmO0Z+ncvpz+Gcv/vkP+sfI4WdyxGM5lctgc3FY/y4SzCjwvBT1jUlRJXdzlGL1ostVtwu/nQUDt08O6TgqXfFuJ4eTBRvv5UfR65IFsJzhyJ/DzUo6h6tJ2vQLqMp4j3PbKTxe3z60Eyss7C+F9v88Gnh1LQqKbsj340JRHLDUmbevmOgfjkqKeo2iAuLg3Y9dF3qunmpaEa7BnBY9Ph20CbRrJKUuzj62JOUqtpdK1ZcVgrMhApc+S/wrRCXh0lIIfPQXlvPGISTqYtKhDzYb4fRWyaNPacKOu034LzOK4DUtnrEps4YO0Gab9MYQ9e5K6l3kqjB6rF9/BRgVq/titYGiqHhnhe4jpJZNCouRfbSI2Bc8W6Zv3A2cwLLFXUBUyW14uJNx1q4TONfMV5D4ziCzlPheUYDzOi8RyQLFLV5gHLbVIhz/lXPbx6i+vXuSG8jG27qvSnRvwVv19yzit+otqJ1runCrTxZsx66LAVnuesDaeOW8xMIlBD1bDiZ210qK5bmNdzcQLBgw4cZzAB07Q0e7FIwm4QnIMxySKYDRMin3r6Aac1v3PEcOyjf7e96mE91Mj+sOZTM/NHlzo/L5RvXeSYaH3AY0sEVrKXeV1mPps6anx6pWK0V9oBiR2Oj4jbfnrjTcPlZRZLrCLAwzq97nWWxYakbBk9hiWklpmSMCaIFFkVZ78Htngn9ZGa0sG3uThK6zODjs5ouYWLN95swZG0sFbTh5ZKmO7gfWYfuLlN+aOcs+EV5g7YjsgMVrWIdpiRa8SUu07XNgax252DtnrVI5Mfe0uUhFGYaW+NSbd9Gw2wzuTFu8Fj958n3r6RzhzSKek3riKsOAe20ILOBPC/oTrCcTCqQ6yuDDzB/2lPL+WuAPH5/LB117s7mb1Pbw4FxOLPYbvxV7kAEn1KG0EaQ0OkbMDOHXJjJrs3EfwMpdxqsRG2Jx3r58LZ9aie72mX5TO0rUCoHuUnEx8GrC6MslCksMgxVl/nwlX7+99InOhA/gsP08jZF9QIX3IliDIC7qwk8heOlVULnWb8FSYuman4ouZntLCEjqy2r84UeR0Yly8++UPPshhaCExpDI4PeHH0CGP13J17dhqBCgF2ZyqT8cQ/IBqPLx/FHkQjNxsT+8EYk/5LILQJG3rtp2AEez+fr5FBD1LLuUO17NNV/ChexSTvTiVGPEus9V/iKxW3PiQ065415iM26QO+bD+mYoRymPDxFzsCoXFJ9bTlyNj9lQFJY7XmEPKq6w/0IiQi+hhLE6Wwy8gytch6hzOO8Ic9kAjdwBr0M7cb5UFcsd38Figbwf0jQ2or1tBYthTgviqe2rljjttBWtFJh76XK8FPaBWS7Ftg9h54XMkeFWSIyqDhwJ7iYo3xhlyFzAGdhy3B+gJgIiwawAhuDPjKLNOqbpUHdYF2XYzIQby15Ci5Bw8H+qFgS+O2gWGhSFNF8x7KmqPqvOrdrxex4E/lXyY1UFSj5GMEZfcDT7X9W9g+pO59QUKFMbunKv7lU/rClQcW2dr9oaqAVU76yao8aJf6kq7mRgKaWm3G7gApZ0cW24Lst+c8FF2Xx7z86X7c9hhmTVSptyTfjxSXn4YiULZXY1gLvHs4ZBhLwIAXjmKxCTSv9XQ/63GuaXWD/bgumDn4BpZ+trAOuktfFpsP7PWl1c838FtKtqjpyIGCwqppJD9bwDTHBlryHDq7mvLPfRosSpFFfNlTuKoQcvwO2fDO5Q9mvoQ4jZoi74fFiiXhNZENJ/dh3umSILQw36D/GZ6Zy7lEL6dykQDFkLJ7x4okFCA0M/gR3c9XLij/SLWjaIWi6hWm6mz8jCYGexHrqOLzy8vQpBKhguoyqG1osOoEvivkWwMwhgR74WgTYxb2jGdUD5iYktrbSfvZ0faZ68nb8T+X/ZzoeF1wZibohnBWczKO4kzA2bbB3Xbayys5AY0r3FF7BPCA/gm0LOZrMzYSdD6PCjIJeJ4398ndzxDVxCtRaqrsdL5Q68mEl8pLc3GR1X8mgscDwN7ndcb68WiivCZQHMNMyb2FF/SO+4miUIpuW0vKdpdNITK2tPGn/niZUMVfj23JffDmkZONF4Nyf+9rWhv/W+CgYRPlbKnadD0xx/Oif8WinQ6uQ1fYR1bz81cQG/XnIrDP8H/Waqfp7CnaYT+CrNd2zC2UbW74bZ7gGr3WKzZLYp84EapYEAqCwRmOUjbIHi8NNWIbP9iULpYmyOx0onbUNLVUGgrc/+zzZsvGriLj0+7AlCMow7aGVKUN9xHCxyLT/m6O1TFmsFEF7ekKT5KYCkdkmyaVzIciluRCsYEHGZICSqfuGGmSj/n99LK151tShTqyvBvSl4PSkYxtMT+mVCTyKrIQGhpfkqkKaW4GWX5MoSRTwDTyvpgQO0cpK5mq8UWy5ZLB4GnXuVqXYDdX2VHTX/s53P2pCc2MOyHheraGgZeXfOOqKle467HDmg2Vr82UcWMNsmbhH33yIeuMX8qhjzfqDcmC3ACPrBHITE85Del7XnN80ilvXUasUTO3WZMqPRTOi5ayhWdZli154PhsMXTsIz7oZtZyCTjM6zHnB4/ipx6/9gGpjwrN5ZWT56CAoTnhYl20kW38+AeoOV/4npEMcUC3LBjAYG+aByAlYZuQPiTQiv/MJ5yC8hRLOeuKBtW0c0EWFfbcRUW3MnxuT7j0FSyOZWeMA6tnkBfYF/0ppKEweVPNsVInO0RFJmmepBYuK0ppKkUKHwnmn/gm1jMX/bNpaUn0k3wSGn1ckbz+pkoo1FieOWqr4Awnepa3wV1lLHjhhtm83qNpdUGFazakb/V6qLFu8UToQiV0V3wpC/3+3X8z9mTtca63LKODSDWqKaIhIwkxCajusnKvkJzFG4vkdMRv8exQiVMbY1NF/TFOoyAI2aC7DgTtKcDtDOpsLCTmwv2mfevmQl1FUUORgM8l11MGI3DqUvrGaVDqUUt+CCq4X811L0eGomDABuJNSd5Jg1uCjDG8X6I+8Iwz9oAfUGQkQv3gsjnOq1ZXJiFu2rFVVrF8gJN5C0eOHUVnOt3DFOsLu6V068Rb+p5vKb9FXzaGyXgoONH3B604rbrzfO42vbJnV0bInNKSd+QXmJ+kz8TIK5HTRj6pT8sSV2l9wB29BI3U36+DLa2P6grvwb6xeG22nVBzvXXJt9zMQd3ogo890EFsvUOZINdaJv2g155QPJG+sFfbSnbmqywW99FyQblpsF5GRDo/l5cbLBNJOss3U2rDT4AeVttfgXz5NFZwl4xPtW62Nzaf8QVDrwSl/r2lWwiGTs0+jiG73Y5mIb1H4O9prGEHv9esdCYQxBn/t/wgZhqcTeM6x8detCRqdQ7Ev6jutfRJASWT+vyQzwWV7HAVRx5UIcJvRxJ9UltCqTvkGIbw9UxY/bktETSd8xuN/nWsRDNNAPCyhXUxxLPukoFz3gQxTmk79nQXyh9dAsX0jpHb9jVwbdcKJg+kEXhUQ14HBFDNj0w1dkFTaTraPtc0Qm3L4/
*/