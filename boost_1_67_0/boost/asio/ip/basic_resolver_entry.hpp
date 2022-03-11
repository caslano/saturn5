//
// ip/basic_resolver_entry.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_BASIC_RESOLVER_ENTRY_HPP
#define BOOST_ASIO_IP_BASIC_RESOLVER_ENTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/string_view.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// An entry produced by a resolver.
/**
 * The boost::asio::ip::basic_resolver_entry class template describes an entry
 * as returned by a resolver.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename InternetProtocol>
class basic_resolver_entry
{
public:
  /// The protocol type associated with the endpoint entry.
  typedef InternetProtocol protocol_type;

  /// The endpoint type associated with the endpoint entry.
  typedef typename InternetProtocol::endpoint endpoint_type;

  /// Default constructor.
  basic_resolver_entry()
  {
  }

  /// Construct with specified endpoint, host name and service name.
  basic_resolver_entry(const endpoint_type& ep,
      BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service)
    : endpoint_(ep),
      host_name_(static_cast<std::string>(host)),
      service_name_(static_cast<std::string>(service))
  {
  }

  /// Get the endpoint associated with the entry.
  endpoint_type endpoint() const
  {
    return endpoint_;
  }

  /// Convert to the endpoint associated with the entry.
  operator endpoint_type() const
  {
    return endpoint_;
  }

  /// Get the host name associated with the entry.
  std::string host_name() const
  {
    return host_name_;
  }

  /// Get the host name associated with the entry.
  template <class Allocator>
  std::basic_string<char, std::char_traits<char>, Allocator> host_name(
      const Allocator& alloc = Allocator()) const
  {
    return std::basic_string<char, std::char_traits<char>, Allocator>(
        host_name_.c_str(), alloc);
  }

  /// Get the service name associated with the entry.
  std::string service_name() const
  {
    return service_name_;
  }

  /// Get the service name associated with the entry.
  template <class Allocator>
  std::basic_string<char, std::char_traits<char>, Allocator> service_name(
      const Allocator& alloc = Allocator()) const
  {
    return std::basic_string<char, std::char_traits<char>, Allocator>(
        service_name_.c_str(), alloc);
  }

private:
  endpoint_type endpoint_;
  std::string host_name_;
  std::string service_name_;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_BASIC_RESOLVER_ENTRY_HPP

/* basic_resolver_entry.hpp
yMi8jj+e44hKYNSfDq28/kOzdghPMyB8IoJByejXw6Gg0vYC1mmli5XcZDv0AxvcyJ30FAX8IomuMMybICKSFJauGcFZo7bnEr7r3sHauhBIe85S7WlnMWky3puZsKW1bjvOAn8xHux8fTXHuaydCj6MlUj3IXLUUpuihd4xt3020L4m+YlXjhGA0Y0EbStMZfQeg1ypG07vSRMhpX7XK1h/FH2o6sUoTnQKODCor6FG+vsZ0NEOr4CNsX0V6AYnn34UFWhZK2euz4X0us05p6ev2qpwfJSKipPLiTazt9wbvY+v1YvdwdGuz0RsnRzg9SX99F8u/QHAQFLE6njGkWYSNh/oDUIY165AZ7qy6nU6rRBfpf9+m1TdtQ994VhSvn4AwX//Bf4J+hP8J+RP6J+wP+F/Iv5E/on6E/0n5k/sn7g/8X8S/iT+SfqT/CflT+qftD/pfzL+ZP7J+pP9J+dP7p+8P/l/Cv4U/in6U/yn5E/pn7I/5X8q/lT+qfpT/afmT+2fuj/1fxr+NP5p+tP8p+VP65+2P+1/Ov50/un60/2n50/vn74//X8G/gz+Gfoz/Gfkz+ifsT/jfyb+TP6Z+jP9Z+bP7J+5P/N/Fv4s/ln6s/xn5c/qn7U/6382/mz+2fqz/Wfnz+6fvT/7fw7+HP45+nP85+TP6Z+zP+d/Lv5c/rn6c/3n5s/tn7s/938e/jz+efrz/Oflz+uftz/vfz7+fP75+vP95+fP759/fwAI/9Yy9mckdMkjYSIqJlQgrqYztbSk/SfMIGtaIleRl+ppwcjXRS0FwPe15vHa6bdhZjVbk5KqSAHf7z1nFmgU6CpoPMh3v38y3bzsnH3DBLf5ktiux+hTYdatcOfE1Umv/hZ+sdbzyzWvVrb5Gte3b7L2iGmbtuOs/+5BLjEJHQVQfv7VMUCFHSQikL+xi0OiRn+oIJH/pvxkdbe8kf/o1TBC68I8i7/9v9PW3+C2KdTK/+z35kynZPVNPjjdl2XnL/ZnraYk641+P72ToZ/l2ZGHPW38FwudxxW4lGc9N6sdfj26fpMuK+p2FwX9zwE3GssfjM54vm8+b6Z3i+T2JcycxcFHgc7Lm/BZsYMwk+5YyfJBv1Qq7FfhFluyqbyHCFbuIeRAr26yVZbFVG/feTlGdt2szsfsn23oLV3DXc18d2ewSajpTe4uv7Feobj7paxwpaHeJhJrO+ep2uDmzR8as681eakmFpR+h2T6jpVeFMr8WcrQLLvoLVvcrjVbbQ9bNdk0AS1d8ZbDTwG/bR2GrVsyV67jl69PIcWRsb0HV4xt8ACPzh5arFu4oc+6rzIul4Zt4IRKbTOX01057vu5bTSpHVHWbODe8vtDvtoeOuHgQt4Q3mTDCmer9uHZExutpFNDD5e71LTxG2V5jLrV223GdmIA17RGWdFhplu4fot69WvQFjLsZdXTjNJIEdEe20YnwAYPHvgbYqVyS0DoynJZcfT89hJaeYX+VYLWcJTmVtylsdjIF6a2B2grp0u2240aeRirPLVsQckYFrLBmqcIoW0sAoHJ0FRCteyGuXqgPdmuTQnjqjzZ+DKRgeZ6zRQ8gKY1GYXF3nRNgDonRudqwqVUpVAGsgcq5KI3AUMBTwFHYdC0tBWhB3qGvbJIgKkB/EwRi36p+f44o10GdlCtoP5IBBbf92WJc8P1dBvHGXVJ7IOAvLb1oe6MeR7T+GxFwpM+wp9+OOrQNpHG/etNyE2LSAtoM9b4EUhz/nL9bjzmDN2uE16vh+49m2TzzabSzVpP7/HG6/hGqwuGgeV4kgzoSbQXAdru50r1hAlq9JGkIJuq2WOgaygQhdtC/h3+dP/vlIm8yqlE0ro/vjzcDvAzJjMxYH2o9hxmjcdF8zZGgXGjUtOGWVrPdexKpTySSlrJO1fZUq6VTlWptTeYaMZEUOrMDF9bsNbSxH40pZpKQInW6YFqSsbP6f2AYqG4GwAf+QiYnpspNZg9fDShmK6Onh041haFqVgbXd+Tcx1JlwxWiZNkFhpRgIK98VuZigKO6w7XnZF4y8IHzGtGA+NcFux7eRija59XIXV0qK43NxJNXmlYJjmUsYPx8cx4KjpRi8QeFlWAR5vhvSndog0xh7OvWrxE5pYR2YTKfHhPCMBmYMpRNqRbgmA+jcIE8Q5xIObIk4ucVxj0UbYkmG9qOMUHfivx1hhQkodM0zV4DjqLKM2khdTObX922E73s0xOzjFIHdoYbxzNld07HkZ5AjK8NYpf+QwJHD+bpETTCheMoxDYoHzDm1NOYFu4L+bTu7lAULeXMhhk+BiPojCbJQKKRUFpJcg8F2GbnoucLpptOeF9LLKcVx6MtBw22TFkb/19FqwtCiMgAMmCS9rszhY8zRiYgNIl+wtRtET2qJvL0wyWDd1JkgZ+jHPAxwGhsnviBynW72T3VrO/62KjZ4f1BfInclkgUKlSKVApcpX/CH9pdDAUX9m+CGSz8QDqhcY2ENyj7P2k5bIVCyQcpBsiHmq+VjoLo37Lnu+BImkcOFKRcySp5P53PDA2Oz2nOm8/mzhn39OvQ6q3qiuql6pvqteqx8tPzT3NXc0JzePtg7ZJhaMfn//R74DzUQ7N/Z8MmLv1Eg5EGp+qbzV0rbTn7Xvux17/9hhePQLjNIU4Khl/sw1kx64JY3TxPiX5705ZzlUVbPhBLAOaHGmvo9p49hBuF3gceBd4G3gZuB2XFpcalxi+G74Z/h3RFtEa0ZgJ6qH9OCnIGWzKuB0TyMYhcfisLMG5DtOQImRF4OVwdgtJGirtkt7v6T06clKU3/Pv/rva7ykrsKz6GWX6BWyGabr7hcdeHhtS8pzqN//GfgO5q40DjBuNy0gX7GPSUzibP2QecTtr52iH6go5c8WlMjXubUmU4Ntp1a4s0y1p3r/8RAEaytx3gxv5MV65djyZ7SPlMSp/ucc0r3zux7bykSQ+ig4qhz78Lr+V98AH1m+nueW6PfFbfQCQxMj1tp+8tbJYvz57OuR4NNZpCjUPrc+M26Vj5Nm54oriPC54N4y5wvuICZsoplws73/oPy5dLoRNlUeRR9jUrKaVcqEkoSmhIKEmoSOhKKEioXrQUhotlc3Zu+wW7BUcFpw9LpwuE0GH/hKpxkBPIgQcZs5s2W8GcIwBJQFHhVyiLs5SlelHBGZ0bwdbelndnUdYJaUyeL4qgwhNSmNTFt7dpqG1MVzGEbVCLDmzOvv/rqs+CtsrsvdqpdpEm7K3as16R4MwFupkG6xMtKBtJ5OHSXd3mMXA7DhHdqwlwJw8ESP6u+CGqp/ZD9prPK8rry5r/O47LLJgN5w3RWHyVbl4pbOQW16PZA5gXvV4Uz5uNv7NlD3ONXNYfIVnjWfNsWXMTP6C/ib+Xv5G/nr+Nkql3OhtSm1VAT4C8eJ0P3xLq64ytjxnPW9fY59p/2Q/bd9gv2g/ZF9kj/dclh6SnpXWaLzofv/e9Hz3zPY8/3R5nXgFeU14vXyRo0J1k39FsEmpFNMZFU/PPvkct9cnl3CQPafYlESCO6gXIxtdI1p0OC937Mo4Ytg7VqwZqIkjyZivHtybVW6eaK1PuwCdFdFDRpXurQd0lDHVpFzRuOxQDpauXEdelZ3V4FzyOBuxmZ3eiF8aiji7Tu2QZdqkXcI6M1BJlqEIrHO8THUao6hU6O13ICvYUKgrK9zUq/O+rYIgi9r48eYJ1N+2BVShrdmsTfvZUNVUzTHH7JRtsrHaXd8rvLRLGxc/o9LUQf+cgWXlelZ7cIQZ4+oUFqbn+bBevYw/KcJG4NZwO2mVbYuhrrH826XJFoOJA1gKLmEx69EMUVR9aDJqj+Hd7+4VqjUdGIc24ikSqhcrNh2Ru/LcyQ51D+JVpaqpk3a6e7XmMdwk/VKM4LR0PZt/M+a212RM7cShSTfFOaVY81jjWWNYU6Gj1D7UxtSprPTzxlpyVXdGJPTbM2s+24JPY2NuDXETdDKrpLGZVzk5ZNhHH93pIO4SPsBaWEDrN8NsM3vjb1zEM6fVTGLjag1zG3DGcuL7vH+kQZ31YTaUdnd2n/bBm/bsnfLXNj3/2Q+6uMGOFuOOqOiG3BNtxrJqUUpqGtuWQY62+OV3p7CUlQUSaT/rVrO+gY47vL9KFtQxLRe4mzUaEsyrO9EtGuovXPLUuhvU3FKmRjgV068zaLnEceo/sqFdgFQyegSs+Cc9vapP6WC4oAYhWHziD3hYM/c57Txfm5S2mxecLK5xdGjihyxAJnvfMxWiLB5Q+eDMl5h/hRVEVteNgfbR1TwziRI26IamRoMiLCoBMxVsrOEhAWbWdV3Nnc0Tpy12CLHNE7vKqtfpM4b47Ihl2whdhZt5kSvxPbXlSRDjVeA5G+uLWa5f3nEv5TRh6ySg2lSp1Lsymx1nrDXY2LrUJOT6AfsBO8LfwR/C/7GFHta7w1vYW83b0xvCO8Ab5xLkcuDyz6U9aq0t45cHLdgIYvuU2rO5sDFRvjpTn0BCoXMHIC/p0Yjgl53gYrmoTQ8uHOGGVyXP4Z0ZZ+gUZh6nTi8r6rgyls9LKoptU0JofzRuQC86b2W7ge8DlElDwZ+PjOiDjU6umWav7hDtZLNCOUkTAAYs+dPUL1CXtWcMB47L6PnA9qtfUqI56SHA9TTsC+JExOplv7onviS+KD4iPobHC6jAkmXXehl3BiTMTn0LTqgpZGOH5xlKc6+8FSHuksRresv5ny1CVPdlA0c3z8jDggtD4S+5sdJkgx7AVEeuf7Y1KIhF4A2OlWuGuTuqAQ4Jd+Z3qZne8Hq+T86RNd1i04/bWEYT+Iyncusi8SotxeYxZR90t0eaEy0ALGHiBnRR/eTNu9nu+FYZ8weVllhHjfvq2d2vs3ytXGdklMfjoidYe6mLtHHPWjupO3W3zZCRjVSKSJsN0flM549W+cXPwShkP9yKGFh8xRNhk85qnAawqR+ekP4Dy7lWxTZ/EtV/y9MdN6fMva/2gO2nWfT/2XhAwYDZuk4TVo4zBcZM+GKJPaVktoLULpaGpPpNOkvbic1nCJEdugYvX2QfNp6vcMmyog+7voeNnYK7306rvY+etH5o3xoj+PjozV9Ky7RzIa1fAIa1B7xBtrFBkhFjxwSP3X31bxX+miPu+t/ePf5UdmCfFbA6d+QnMVnDMklldTxytOFpFektxjhfqiX5mc2yhYlUgN/lOcRC3tx2HJx+0OodXXjJEKMeAWjlxxOsxrbg6VFusZ25KcUAehm6Iz1jw2ij+lJj+3LVWHNYP35f/Duxh1I6t+w+27btVLxz2A+irjv63rnurJRPGqnlZB6inHsjgJ4bP+MUmTI/OAwF51xsx9Z32XJM96doVPfRNJ5HXPsiffUj424vkNhaauw/F32fpEot2AyfyiEHVdn48kHslH3Qu9gi4vyclfpoJFUUty2vctYgbBN+PhHcP4QKIJLESmEhv134osQciZMkQSzqOR12qzsC0sBmfFax2wWDHUIPXX4OO24xtUdpIMYMif5QAEY8YR3TmyCojHgBSflEiidOVpKBZb99N1CSd+HFjDxYWFgAUIFx0lS4knYA3Og5ehio66FlB7sBhfOyA3Pq7xakJV4tiuV9QRMPCq9WAJmPXNlMuaucWK3FJeO3ctgrEiGitAb0GCLkwVmRs1nwffQ8yt5VV6pVZSFcm55oTaQsuM2ZrErKQtI5sbmoGMbwZdC2L0aLye2OeLGu5xaQ7Dg2trx0e6iRXrNnfeSFABEj7ArinqEwBtQFAzk8vqa37FORzpEiCol3O3Ln4gEi3COossI6qqhslTIdBWKMp9y8d7zb5dO3f4Sz2/ZgIqZXKopqsJwRMB8LDKAi901AwremS3Z7vVdpjp41z6Gy3DT5lIwVeModYGKhF4xgWuOI9xLnX/INuMcfZE8Z6B9Xg8NDliFOnS2sDKzZX8QCJVXqzO1COoadMVXBEwFNWyhPuH+q+KpjW1UUwTc92F8ApAKH2Yo5iooVe85akx5lbxK8YM0Su1Rjt0R2I+7Pc9QiwIsmB9qpkYOspt/qbqMboKjBKzr4+bh3BpKY9JMOO241bBZCmPGoE1JobmsP5KQ9laEIOcB1XPBYZaiOtJLoa4mMQkUPCdelp+FIGOkH9a3YO7vWjKCZM/aY8wuM4nNiuI/35Et3iRxQdXQEgYdYQvyX6Dn8fBV/OVtNfSLdf4X5Nuu/whDsx7PffiuZTXaiXFS/Y+bCLIx+xM8PGSTSfmvrrevIFkFdYczdLQgdsoctv/Z7aMB8PQAfdJ84kyW+lEiCt2DGjf4saLukjU+jJoiiuwt/X9JBUibwPGL7Ec3wrTb9wdPeziDG1liUR+60qta7Lm1akiMYsO1pNIUaQHufVTA9NZFWRbCGULPARJakVhtqJGogo8YOJ1zo318svArDgUhflVk5oyYfA6oj4u3l+FU1MYvFt7qD1GcleTPWJVdAMcB3TzOpQ9FTG57IU+aKOQgPfNfWMEwWrDahmzMJa02/tNan/h7q62pT+yqUaqRdRJC4Mmh52M0dcbczsD5zrEVuiHHZH9MGloA2/dOSze9KnZMF2x+tjvHNBC5gS/0Lv/3PqkLAu/gZrMZ+1TfRUYaSlVb7dr3BF0NHP33Pv6zT2WlWl1t8iyv/n/6QNDQLGy6BIzz1NgLps05LP6WAalbOIem+to33D024Fyu0RyX9ffhn2g/VVVtBAHkX3K7X74VxO8SIPJ7OKMJmM7GjQfbF0tSs3FZ1tE4990i/pRoWIFcJBvYmiTBZd/yatPsk0L2ZIoBEjcOv/04VRmZ2D4t0gw4R1fQRMHgphQMs9gplExUqXwwbVV+j4qWjQc2Ed22yf6GdmdMsvlTGfaXWmRlJezUoeobUVJ39ve/yPGc/OEA0HBfqk9tJkRTw0th2LSNrQPVsleRlCACe3ToIxxR5sNoJOjJ86X1vcKPAXkD6AAd9GNsb7GdIw3fEIlna2trG52EmUnk6x2H7A651LS6SerJOqDvCqSzMwm+OTwtWIxp/B+rsY07sPqy0w5J3nflpsUnly4C3+cO+7++iotlbY7ZJ94RaBPeKqzD0BJWMNUHtOKTHJpV6XQqJ01eSiVN0XtDG6T3wZLFzrvRd0kUI1KGr23PsZs0hh7u6S2govaJgOBUA9Hx8514O3OeGqDYt4iHcx8DP+RYV/za6+bqXzKNoWfcJa17UzQlkV/MCNgDc1RBDVgboiY4MKg9t2QXnhwvG86bmIBXJBAaMhbZ11THTaNDzc1ClUCzr0B58WsC7SZwpk/GTMV1sYoYWJCnaE3SemLzF5xH/4QuWmkzGAFeMQJ/oZQKUtCN73hQS91xTBuz20A1Kx+I6djNT1JH6S9cTyi9Tx72reECfehES6alK8q798M0tLPn8yN6zWqvI3fFnFomgxL6dTUziFNDFhU2wezDbGVFg9WaiRrp+dK10t1RPblyfkLEv6+8omCrnTAMX6+mZZ2Mjo3K8g2d7Z3Pnnm75l7YvbcopMvaPsFhgp9YVET5N2ryS4finRlT62cDLqoH/aUBXTUALiPFo0sCuaiWTno4ZL9wLw/H5Tva7pBsy0xCVp14UVu7zaFe5vXzDitLdcmHayVhP2JU2zMyQTCRGzp2BkFGKZwT6BMKTrasnF5M0B3wuYNA1/IJDXRaBhRtZNdLhMoJDnYbrRHOVTV9JcpsWC5H/VYKOld9/m7PL2J887zaOvZMHZEb5nVSlM108RLhIa79RT/A6c9Ys1mWbiMY4uUGcbqlLXqntqxOpGdM9cNA6KawPBgVcZeuoYIMHtQlQSmJ/UzSRCmlIPETuu+O4G0MCk/A9QdZFZqIqjhWWqtdzCHWpykOLU7LJvpLN1pjeufvY0f2Svm9DBplV6dmf1HvTJpiR95u762wxQy7gvmt6zbBXcHnUXnf7dNw6nhJrQfslhx3e2lfKk9qxg7j12htHo0/onXoF2aBKzb4prOWoocarpny0JkUY9mNEfLQ32S47Wq4p7Hh9U6FoytxGW856nlau4DJW1XAgmNIaPXy0raLJrGXa1vNC/zxg/5mRKhky85VzTlBxiJAu9vkp18y5ZaWU0XCFJZrTiFzQeX5rPD5zTYN4OpGO1NVpo1H9hKkdreO4eF2K5Oh7fD3fcTMuPqDir80T3juF+Jr6QY131fQ4v29i5RLoNuEnhuCfWtSo2JRc94gHGdM4YxWRCk33JkVl+NAxcghyoXhVgqHJRmQNhQ1rfUC8M1MExgrTlxOb1h/RKkzsnGQYDl5zujeMs+S8EAwZdd1flGXkEdiTCskH7AE9jYjgtsH1yxngPccEmPjBlsgMqrC0scCE8rGtNXWd3hfX1Cmp7P2vm8PtXSTcPW27blp9fpb6jcX8rJI6Yg3QbEa8/1hYTdTssDqrIEDbjNDZ3mPjZujt+GS+7cemjqc/FHmfbAlHp77sLaAQnDb/R7s65/hQUMHOzyK1fMl8n6eNea6Gx5NmqXAZefniM0hGJpgmO4FYLjBIkX+M8SYqbU3qlTyzZ9bzFONTecIkA0kgD5xs4QOkKbnD8lukl4OSZ9mtQTOdbAQasAyNO6h2+ptFiSSiJWeR/MeH7rWWaYdcEB47lfHuK/w53N1awu2M/QiFYvESugLV0De6p+frv6DLnheiMyhlvukbHDqb/TghqxeD+EF+CEbw21en0RGuuclxkvVuhruVdq7D6r3kPFfT8EHLxqL1d6j5BUg+sjttYZrlp7BKuMwNo63u8glp3uLBfE2jou0GkVq9DXGrO/gsYeGxM0bUL5uCwmVUJ8xZNiafnhfGlvSx4sMcmQC3QZYTMfAGmtHxTcUH8y4CzhsKWPZqnZzwj3ZogDFX9LkEGiSfqZDRcOOwCV6/kiUEzuTGhyyG/MjENWWwHPhIRpoQ5UQKQ+UPUnWjYRGzHc1hwYpcNwCeOknu4V6SumA1tweit+96UlQMz4+r/9wonc9tJSZuLsKxMmt+wpi9GJ7teLgtlUWFQvaeLieaqHOmk8TnvAh9qtRkKp4vqWRwMdS9MUPxWHuxKuDj6mpAb3AuV+H49K2tOGtXDsfFIpL86vG0FrK1HuySObcsAlO1SnI20pEjGhDROUWSMGr17XWIshZ1Q/WbqSzzqDWcIIINlB9+GY9/VtEdUtDVbZM=
*/