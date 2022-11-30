//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REVERSE_HPP
#define BOOST_COMPUTE_ALGORITHM_REVERSE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator>
struct reverse_kernel : public meta_kernel
{
    reverse_kernel(Iterator first, Iterator last)
        : meta_kernel("reverse")
    {
        typedef typename std::iterator_traits<Iterator>::value_type value_type;

        // store size of the range
        m_size = detail::iterator_range_size(first, last);
        add_set_arg<const cl_uint>("size", static_cast<const cl_uint>(m_size));

        *this <<
            decl<cl_uint>("i") << " = get_global_id(0);\n" <<
            decl<cl_uint>("j") << " = size - get_global_id(0) - 1;\n" <<
            decl<value_type>("tmp") << "=" << first[var<cl_uint>("i")] << ";\n" <<
            first[var<cl_uint>("i")] << "=" << first[var<cl_uint>("j")] << ";\n" <<
            first[var<cl_uint>("j")] << "= tmp;\n";
    }

    void exec(command_queue &queue)
    {
        exec_1d(queue, 0, m_size / 2);
    }

    size_t m_size;
};

} // end detail namespace

/// Reverses the elements in the range [\p first, \p last).
///
/// Space complexity: \Omega(1)
///
/// \see reverse_copy()
template<class Iterator>
inline void reverse(Iterator first,
                    Iterator last,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    size_t count = detail::iterator_range_size(first, last);
    if(count < 2){
        return;
    }

    detail::reverse_kernel<Iterator> kernel(first, last);

    kernel.exec(queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REVERSE_HPP

/* reverse.hpp
MO0g/kNIX2edZBrdLWYVGLIUDdjPiwuBk8CF7mbRkeqOgtjYl1mVvrOyS59lpK3Lz29KHOgXiDYrC2FOCCaUDXbhdXNzWLdxoyoto36deQmnx2gHSyY8DMqB6uzg90NH+1w3ZmJQjQP8llikSo/lAyVdZvaEEu3BPcif9ZiAyPZ529eaIZ1WCZhbqWOXClS1lbZ1QOqU2SBHs3eiWBL0/wFFHITnS9Z53lX1ChtVYh3G7O/kO91xbuTYFSVla3+yP6awE4dh75PytUxOQJNOclL1jiqKEnvWBUImubZ+ljV0xPWgDOXtSTyl5WtnaxV/5hbrPOiQJ0F9h0ZARMcNoQmkLGGOb3+PnqCYScAZFiBgkHKTbOcEXfmx1PypFHKsY92ayFsOacvSDzbJmY9h1/F+QG+irLZnFc/8LWrzZIsdDnRv0hmr/WqNiXWhjk7tuM8MHXHNhYHpLvXWrOskqTtd9DHBg3Nu1D3rjmfdCUVgYdZM+Zkub2/3gkn9HO+1OvPjDH3vyPwKjKLwYAhXCHhMZSmGcA/OGt64qqdmJMCSpweqypX8xRfjD86noHAEepepi8cZwpkT4nmg5AAELPvTNKCsBGDkthR1xNGG4JD8of9A/AY4nF8K+x+6Ylqb27KEPsqhvvyatw7z9qPiiEgJGIwoPbSdIudCh18fzj5f5iqnsQbgPxwTFG2sWX2CpUFs82/Cq5tBz6hV7c1dtqVmm6QsIz5gVIXDqbNmXHV27DaBGUix0RQDGQmuhcmKvn5+fgKEAAACfwX9Cv4V8iv0V9iv8F8RvyJ/Rf2K/hXzK/ZX3K/4Xwm/En8l/Ur+lfIr9Vfar/RfGb8yf2X9yv6V8yv3V96v/F8Fvwp/Ff0q/lXyq/RX2a/yXxW/Kn9V/ar+VfOr9lfdr/pfDb8afzX9av7V8qv1V9uv9l8dvzp/df3q/tXzq/dX36/+XwO/Bn8N/Rr+NfJr9NfYr/FfE7/+/Zr8NfVr+tfMr9lfc7/mfy38Wvy19Gv518qv1V9rv9Z/bfza/LX1a/vXzq/dX3u/9n8d/Dr8dfTr+NfJr9NfZ7/Of138uvx19ev6182v2193v+5/Pfx6/PX06/nXy6/XX2+/3n99/Pr89fXr+xeA8O/8e/aSd5lBPv1I7mdBD6K1mzLxdlvydwqNhp9cGOqu3IvdD0zOtTErMojO3YHOSvvO5PxbUf8Wv0ZfH8BGwgBYv7l1BT6Xc2cU5b/LagMNr9eEuxxKWo5xo+jadu/uYFX5k7idHK0ClyJCQ74ZUgZiGGGraZdjjdiAH8+TQasKAiWWffT7qgK0ZoDQTZNdqi0qrrlq0FtFVaLuFKCjAUZw8r335UbYNru8MKpMiHc4YGFZgH7MYLvNl2ZypMN2qBNenpCeWa8u0M31fEcfBOGlRdqN8G1ZVnN33jDrMy2s+VxOecDvswBP34VjHmzW9rw2zNDrtYDyqRLIYm99eTyXT5u0ToFme8khF8+Lp/RfGsmRC0du6a0Txgd4DbfqiAXIvsVT4UlQJdfJ5IcqnjX4iYKQ7Ig/aRpwg2Y5Lgn2EX24AmgFPtA6ZUZnA2LKakG/gqpEMGCAjTd6CHdwvQgcRL3lHuWQZhW+tzmcsB3idm3lUJRtR19DUSAZrSv/8DYUHPwDpDHTAjjKo643qW/627Z8rmQI5wM70pLNZR+W1vP3LC72wwT+Cyd7Bo+jaHOcpj/B3H6FCMPB6Ys7biit/e5UCN2AMkjg0RKc/qTQFwfvh2QPOARUXVU0t1ZzQm6TK4iCDl8QRQYT/YnwCXbWHkphIFsG6To8H4muR9YkCuHoDyEeY+RGWq1aF+Fre96/xBwOqao3MhYTdULfOBbdqncIpnJYRFon91Qx70HMdqz6E4YdDgGG9zlITZDBw17IZ+ybvE8sC/nau6pxFTL3ZWnVxkEOkQJphJGi2tzhH5Cjxz+N3FYOSdJzchLy4Jzh2Vf+09zndGZLollx7yENeBvq2Dl4yRcBPrwHPo87V0wfSRcYiu880tcCPzpRnQvoUWgrhBWa+vmCZDb//OA0HHGhNlZYPTOXBOLBLvAABNiyILGMvHO0wYt8YvOXQbl+Is2lWOnnxN2se/QwBpsKRXt6i0jG9GgEvv1FBoymuMVj/8AJHp7tgwgnESJAZhAwEjZUpxEMUO8M6Yuf/vyL8LyP6FydLBCxlxl8xcyIemrnAMA78gGRoWRtIeHmoMIHmI36qXHHcAKQ2HvpFb77YK+ocoi83rB9wl2IbD3ryXbvUb3o7OgirrAdnEKepqmY8kQ3MlumAyJhBXzGA7pk8MXwltn3PHwnHRiRTMWWNrl6N3b441NmzQ0kMsFktKFzy4rhUk9Ja6ZWErnjtSu4P+b4b2lcrW38vOv8mcRon890pHpa0l80tzc+Cbtn5JFbckxuzpI74ig2S4aRL0uRGTSZ5dFu7HJoRm4kufkzEtdazqhLIwO8AupaqSMCTT1vEnRc6QnCwnyXaR7hCo+J2Sk5bVFM3M+nR7lVMpPqEqNCxFsbI21xbm9OFC3DZxuRLBfMpL2OdRitkeyGw2xpqm14QiZxYQnNwOG9869ze/L46Hh4NyrwzMTUeK6TjYGFOSOf4aL+IrpdIfM6ZdsQXHcTqe0WlpVMAxAccr2I8CYbIWUW4ba7tjqOua+AHPhs3YyZahZzEy/2GDFGDrEJNZjTKKEh/YiWcVw+mWzGfIp456KOhl8EDROZgavqEtn6rjc2sh7w2yNr00780l8buIsFPQRV/Htuoo+Azp4HDDgyPrnXwyoRCf7Xwnczw07K8LgR5m6HEuZ7vXsxm7kMNOAySbCPH5B5//AWAGSbGGYFqYZ44Kc21OW2fjLNzZDWWKmzZ3tKsXmlBUFy6Ta/g91y4SCQtL/YkiZN5hCSjwzk+gkHOeotwENH5+Dtm67delTHpdzoqxAHtbgsAOGxeRWFCVfl2aeD0OYhDrEJgPDllBSs25DlypMPm3joORRGMMfTQgxKp/o2DuCW4l1TDbBvSPO4ciSqRAyDUUQvxUyRpgtCYXOheqhgbXKavjE9h61QWLVZeU/F7JXwxAanjZyVKfwZy6nnVR3YfH7uc8JZ8eIDUCHlrxIh/HZW+gOYBlkDZ6inlpHjBjKVKzdUH/lcR5JQ2YCC+zMlidosCeOjq2hEZgvoTwc0D6eNuKMCdIUMlJXU9oLerwbh+LJsMoPlebDlqquEAK2aSK0rB4IVoyDdd6wVjZtPjLXhQSW+DgW5KQU+hchCXObeaDBLyQXLpLXSlxSzVPBE22xjwYm1YyiCGAUQGeixjcCcZaDV5gbcA7FewbDFFGsA7CZRy2Zqopbeg0kGmvhNs4TDsTtAEoY/I4xmUzbivCqgrNpgXQUX+J9QjLqNxo2MBaoELM2ZScAHwgRJjuteQ2fWXWM1eTDQWuV/rednrZVgnPif9YFRR4PyxFt8naamZwCdiXfhIV4Tm3nNjW38CQHGyEGl95hZONcidkha43KoWknY5W0U5nk+UzknZtMq1o2Qbyv33DSNTVyP47heQ2fNGEY/evaD6r3xvEpx7Za5HBLgRco4pa3Bcu7A6oOv+1lhGqORrIlh119pWAesjypo0aXJ+ZkrMFkdknM/fmRLbmhUT+ehmRmL9HqiowR7A1WkO87EXOTLTqPy0BX8kg0AeDrA7tZS94mFLHzZgnLPUdeR6SQwgYFuuzHLE3R3LTPsSj35WW2Kpe6T2pNwks7R+cHdtv8eOmL5C2nZlt62KvUKEkeVEihNPbRQYeYApXpEh6GhYMPTMygbJg8YZbAO3T99geHybFCy40zTITs94AKB1jw+3HjH3AUykS5DNX2hOD35yQzU7Fz4EyKTONSduCtPJitPyg7rnubT8xntpnaXHcVo2b1bWwSzClE3Ydti/FVaV0ZAeJQM1YX0ZX6asO52IBLdrp5coi49vABVmiNscCjR5ZCqnYxNmRp0m41M1O56dRt9Gzp5dAtxy7c7mjejBxPNYhvLPaF/OiVSlgGHplc2KoLylB+DxRgZfPxGAoPnLDmRle8FehWB9sZn/PYOG5XJvGtMEHeXtsilMc4/GGzQ9jpcbAzRZUjHPSy/oByT8NpX482B8A5KBKVdEYXSp4EuGfBl/eSebyyiD0+lVfsJdz/y+ip2xyag15KO23GVeIY2/yO/AU4+MuoDKYgogz1I4SzMEKUIxGkBgHtqJnUGwAduMzdMgjGPfjv5gI8+lzkG63hm5IKAbEYSbrHTM8z9kC3YE6agx1a283kJFWksLXIA+LNAeyJ9Qr48pSbCAARJZZAlpBRN+BhY+wGU/8B3O21q/Zl0bRt3xz3v4t8zqoK1HkIoShYtdMFf9AXkE2oFACyeEvQwmNKWNzm6bRn/KA4uyiW58LJPv2Ht2OfFeD2nG2Pzp1ytnuJ490VEBp+2B4xTdLM0pVvGNG3agUs0x8BFNaVQjHEU8421KFQTn4D2MyQz2NCZWPOSuDruBr4rsRNJPHjFgDQnBCwTQTQlZP7Elmg7CbsIhPfTtOOmMQ8nZI8K8lbLNXt4lWkaQlcA9oqqmFOmIIZcHPLzIJOiRh7Xu50g9Yj6N2MGMAqDbOF7XI/b837ReeJjXT7iOYueqpczgOtSPmf92WxGWRNMTJhY3k/NWJYdjdUkJHm94Cf46k/gZ1kPrm3tMoqXlIxiQ9QlGm86vAUnECtqpKiRZglo96FDLRA3LzMSbuDLmfY+mazlkx8MvcjzAKn0fIZy+4YA3s5r6iNWG50iOVUiMIsDdYhS5VBQZN5Xu3uzMot+xcWlcVYJ2S1wMwGT4iT+Q9KjZmo5gjGMl/0jpz8aq0pUDWqu6whHTF8e23bRvIphko8mpVajERZyQsgdbbu3/y07LIc3bMsAuwN+nMhLrlFjM2aVx0QXV6AY/zSseJHiquSHuXCcsWvqNmV01gACzw8esMB9mVcu0w+x+9oMMqsLTgHnOs8uTjD0QW2JvwPNVU3zto38c9AuUKvAwUwZ0qHc6kBmXeiqDPNheZJLz03+Ou7xPW67QH2vovMqceP5Cac//Km0h8/HJJ4ustRNBGa0o5IHyiuBz04/jG1RU4cSRpc2YAX3pABSZMUQB9N0zRtIBDCC6uGCfHXOCJqj4+xWhTA4JJM5uxCvtQyFxd59XWHPwA0bSr4xdwEFf38bSEM1FjfaLZZ/InmKKRSIZQXIOcpfsfsh22eauqF/MOEVlSaK/bOCBrNlPENdB4jb91faJv9Pa2GJigsKH+Qi2DmDfAjBzwygeU1d5ovtUDzEUg/WGSufI/D61oY6dWPIZeLDV8nbV51CYuD+l0FEmynpPYInvDG6rjoAg72Qv9nde/0y91bszGkzGO2uDHzVv7PHmq3cw4mF5NfNbotLMNhI3j50vKd+0CbyB269j5lqMSc95gfnozfOAbQmqXNLb3Ug2v71yaqOWtIzZJXLv9UKgSdkBB5sFmXbWHL6q335dBSTrjR92EozhSdXC1C0/OZQp8DO2H9ho/64RAGAGcMaq7oo72wEgC3quA4k5AiOM5qTerzvZwvm5MbWPvZ73qSeV8fZezv3UtrK+lchbFcH47JegxWEqaxB/mB17DXSyTJ6kkd+8irThXuD5d2Igz/zAOhgHim9sqGvkRLcjTJeZbvyl9G2DtsagguEveRpHdpce8hX55SD67oCE+STvGDjUVWt89DTjbBnH+iHiWH+qRDT3LOzBsnlLsc/5ethyKBc9AJ/R5YuXhORLsakToLjH+SI6kMiWL7PGNd02QmrOlp1N6TtHdB7JmMNO4wu65GNkvpBnSrZio8x9NnK5YdDoP2pgAXu/cPJphcO/UzWU0/B2gffHVDgiSOKr0PfBmU5M+aTFV8oqIpcReqxm5VvNgqc1WwHhtcz7Rzbgy4AUE6WP0Khw1FGLWaf91l4x79TqBBwpucDxSWGAn78l70f55owmzCcIwkEWGSOYpRTrcc2HggAGqtZnFjAkvH3EgOxwFQBJH59Vr7VxYB8CQtA/9zKoe33z3X6/6g9CgJm8H09IXll8ZHUEKmGimZfCslcUKiK+CKeRdZDH2gn3+p9orpB+ntdMUQJj1bme24/oXmHwkQ+dKt0j/Rk82MHAGBTZ7t2hWsSU1Jg9rvVE8yK6JdG80d3hWar3Cy8I6GBDPpB6pCB//tEFiBqgisrFS+Az6YNOvybhT1A0QE9jRluTf1z+icySNn8KUQ3sLQWbXFWtxXZtaAwizdJVna47cVc28LaSGc/brqGnVvKGgoMlyAiqp54mDC6lGZDI9hfLciV3qPITbcvJEuF8yzUqhHQke+b1nCxo22rHG6kFXyktPo0xUVpsVeRc18i6OtiP185L9rKjOneqhi48a23Sx/GhciQ2ekA85+T1iYx1kqrhVGlSBaPEPMsnR44bbscJDFsDKcPAeA5k7vJwQMUP4ajNeELZr+LfOUoRDNGQdQPbaoxadfMH0XRlGOe0hYggVe0NdW8YHTHs9M7UQFHPJScEGSN4rOLiD1UnkSHLzcDfMmTTYHrae5Pb6T3c5fLCWkQ//qDUX7cdxyuMMVIft4OR7yfl1ZSyjOWDSfameCQmuG2uDG9RkpdKcibxGls0sfuaMDBR3DJe+blDqaz2cTisx7/oSulR96hE1gnBdQhf3Hvo7IxSsFAJrsL5IMnRTGajZleN9DTgtZaou4X5u4Bfz0R8P7+/kP/7U+vqN7IUmqnk2BvCx8SSYnmMR7GSlBj6G+s5ZCUUJElOpeYgq4xuAV6aJAPeERk39e68kx941igRxxhHapWymrQpYYA656PAYCwOwz8wr94jfJd6VjQb1QJHSEdmkqAlBVF/Wv8XxKeQdfs+p+L5dOlF9iZNKtpy3EbbzSsZH0Nu/u3gX4ORCOAMCdIjfmqewAF6qSQbEbdTbr0PAg/UQLduaiT2NwTHg7hIlmo3O74PJeEeugw2bMFqXgLUrEXxdV3Y4G0bXZP5X3LUPfptaDeiofHMtQZxTifA483s6KRNetuin59o4WBXSGr0VV/8Wzi4guOi50V0zeDxca3xkME5SwaOataCXIltfuhGhnZvVub2+zi6761Ymmp7kdH6vd5xUOs3UaRdJb38fok954zZRDxgfZohI7qGJfgoKDn0RgKCcJqS/ggEt+/Nkm0vuc/CU90UnHGiE/PrKjzvMo/meIlj2XBJC6x+08HtHv2uWkIw8Td0thqXeny8x162dHDaUexTx24rIfSMQ5n8RJ8ANUPL3ZrKu3ZyHm9IsomMqzeQrhgCit0g4+u4hZFS+5X6d/Oabp2xvPp07B70TsDH6v3+4a5VhQ4ImizMFrUMyNXB9wBv89b9eP1CHxkDBK+EpEXfG6fCcVs167hDeA9Ii7PnbsdJ6+M1ERZ4kmWJNCHtWXeWD2Eynd07NCUaN4ASpcSs+2WgDUSPx736W58UYtB4LmTYdnnNswLPkdwOjQm52/Cd5CJ/BXx8uABp4SjyXDlaBTUQoBe4j9k8DtGx3mW521jN5+GMHAZzIpamz4gqUOQkj1pHNQOo95ZpCNQXWkL94mJ8VVjGr75krxh3ZSOtlzni2zy/FEo5EGLiKgwjv+CkoiaIgraY8mU29wW9tWY2dIs
*/