/*
  [auto_generated]
  boost/numeric/odeint/external/eigen/eigen_algebra.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2013 Christian Shelton
  Copyright 2013 Karsten Ahnert

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_ALGEBRA_HPP_INCLUDED

#include <Eigen/Dense>
#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>

// Necessary routines for Eigen matrices to work with vector_space_algebra
// from odeint
// (that is, it lets odeint treat the eigen matrices correctly, knowing
// how to add, multiply, compute the norm, etc)
namespace Eigen {

template<typename D>
inline const
typename Eigen::CwiseBinaryOp<
    internal::scalar_sum_op<typename internal::traits<D>::Scalar>,
    typename DenseBase<D>::ConstantReturnType,
    const D>
operator+(const typename Eigen::MatrixBase<D> &m,
          const typename Eigen::internal::traits<D>::Scalar &s) {
    return CwiseBinaryOp<
        internal::scalar_sum_op<typename internal::traits<D>::Scalar>,
        typename DenseBase<D>::ConstantReturnType,
        const D>(DenseBase<D>::Constant(m.rows(), m.cols(), s), m.derived());
}

template<typename D>
inline const
typename Eigen::CwiseBinaryOp<
    internal::scalar_sum_op<typename internal::traits<D>::Scalar>,
    typename DenseBase<D>::ConstantReturnType,
    const D>
operator+(const typename Eigen::internal::traits<D>::Scalar &s,
          const typename Eigen::MatrixBase<D> &m) {
    return CwiseBinaryOp<
        internal::scalar_sum_op<typename internal::traits<D>::Scalar>,
        typename DenseBase<D>::ConstantReturnType,
        const D>(DenseBase<D>::Constant(m.rows(), m.cols(), s), m.derived());
}

template<typename D1,typename D2>
inline const
typename Eigen::CwiseBinaryOp<
    typename Eigen::internal::scalar_quotient_op<
        typename Eigen::internal::traits<D1>::Scalar>,
    const D1, const D2>
operator/(const Eigen::MatrixBase<D1> &x1, const Eigen::MatrixBase<D2> &x2) {
    return x1.cwiseQuotient(x2);
}


template< typename D >
inline const 
typename Eigen::CwiseUnaryOp<
    typename Eigen::internal::scalar_abs_op<
        typename Eigen::internal::traits< D >::Scalar > ,
        const D >
abs( const Eigen::MatrixBase< D > &m ) {
    return m.cwiseAbs();
}

} // end Eigen namespace


namespace boost {
namespace numeric {
namespace odeint {

template<typename B,int S1,int S2,int O, int M1, int M2>
struct vector_space_norm_inf< Eigen::Matrix<B,S1,S2,O,M1,M2> >
{
    typedef B result_type;
    result_type operator()( const Eigen::Matrix<B,S1,S2,O,M1,M2> &m ) const
    {
        return m.template lpNorm<Eigen::Infinity>();
    }
};

} } } // end boost::numeric::odeint namespace

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_ALGEBRA_HPP_INCLUDED

/* eigen_algebra.hpp
dSnW2wqLrKRapQtVM7Sd6yAqaFtSYEzcR8nSh/dlUxhUzb/NK5v66DDq0MN6h1xWzUqzgfiwm5i8LJxy7giN7WzrwHrsVALZPwpVBdNUtfDZSUYFZRmCAQ8VwE3u7L6BFby/OKGCvywe3AN5xR6EEiv45WKjB0rZ7FEdeV+++m8Eo5tO6/D7E9yt6dXht47uuK8AwMt09AbVM/N+o6U5eFA8BRn3xhhjZVr2smP9470JXTUPMdaM0Vca66uJFey7d/BsH7jibC9LrKDm3sQeFE4hqGUIXP1dlW/5Y/vaHRcjEQWW9tBWutb15raXqD2jGXvty/QmruYb42oOFk6x0PWdqpLKf9WBVvmHgbCGWcrulchfuXpYqGYGXewP7k4z6/edhFv357QwjdY09W8D/c9Czr5gD9GU30shbAwPf7ayDMEE2lyiJcnht1NnOfL0AauWNCBErx5Phg0OYXyUd9D/TTFqEVGHdBpfgwCPSDBy/w/sJv3pWb+VSGS5kJ5ob6HEIHk8x7MN2HxlbjoiTsy3cPhr5Q7bVphmY1sA2r5ppnNzbWBz/MPoPt24t5j8lmBxelJ5wc9eRzg/Re8G90IZbGpyl75mIk58URmLp7LUy7gQLYdzWmDuLPJhNa98bzTOjazVb+bfLUqVxL87+Hc7/+5UiQb5dw//tvBvO/8ibfFuTv9Zj+PfrTVsYwdJpLGOHKs52MViuGNLl+w37F045ge8RkEOnmB1shV5GostymrOmT6U/6jLBpO400bytSUxO7ZE+vz1z77c/7Mt1f+zaDx8wcOH5K6N9aqmmAWaPytUvEpWK/p3JKenUh61hmSvS/DsMG1iQIYVUOF+0K4Eo1R+yoNRooKA/2f5FtPQmUZZP64HqPQhuMy7MxB5d0t0cQhn89Til5h69pZtYlZ4T3RxiMnlb1r4mwP8DWcUX8Ox8mjG4SupFk+sO8zfcuZpBnFegITBB8uvMPjHKgnmb2e711woWieKZHE7H0Pt8teLoK0X48TsTB8TzK4LpcHWVXIqKjwbeCdGRzX7suP8Yx/57MvzgwtXes6HCtByy8oD1xA45RzSrJrbMphQSzNp3tO5GwHuAWsupz/1f1f/OyHvHf+IV9ufhQ7jdLhAjNpBl+Hb6Gka1Czys1uAHvDODktU+RHu3RaqEJ7z+eXK15Hoz5ANqdCQrDKYb2mEPrf2TQajRsVobVaZBPJNBL+PjMw//Tk9fHoNa+MrhjOMd9xMO/ldhCZxuEPe7hJ+ePqWqLZN7QREXdKQD7hbKb1Crp5obLUkPbdzO4de6/HoiqAMvYHpSCWIsGu4ybxVr6dHD6q12JYTCa62XgqkYcWmlfdA4oxV66O5Ft40T0lpyClxHBYCfq2YBVeX5u0m4n2EMAv3NB+HXS5c4ZZHw+BgV5TFONhVIEtW6bYrhK9Gsf11t3+ZWBDjKG4qA/v7VhA0/z+UGTR/PjRNRPMjtbBHuLo8ZaWcuBpqqDSEVCmwaLMs2hjROtTSi8XpoqqL2LcUc9VpyMVPJ1F1uzgH7ll/GiShyaH5w1KR+Px8eIoc/sv39BSk01I5BenH/hEh21z1erjwdocss6njjL66tRla0ZAAFy9PzxiQz9UnPs+JaIul1gxEm8u+4/5AbpUtsDKXoSVQjmxWbX4fTE5KCOjdWlWvVtUXGT8fLHVpVsjVa6R6R3pTV6/bE9oI1FuijB4VCs9rC1zLQcKU6vy5RwzriTZ+bQBLWswhZSY68a2v2mBXrEHC1i/k8nACWdz3R7+GvqerwQVsuc07eBP8EAgQABKcfIkA5O6FjCAY+9Ja05CztKYs5nh5u4wRs8sjHVozbvI+9f/IF/6+KF7hkYFTAK9RCxlCqM/+DCqanssWEwEb0lC0yyOXLkbCt1Cp8QigkX3pTIS+Ga5w2HJ2xXZK8XyPgfHA83+A8E2f+jmAzGvFvZHc1Sv8d4rC6aJ4hiibCRPuwgLYF3p7Eeay618JUAoq3XF+VzQ0YsbLk2AwguS09Hj9YwOtS4c/HLNiMfKtIsVvwW0W0FO1kFnKf8qm+aFuXF3KuPdbCAYG/2yFdicG3y4HwAVG57QQdcAiyMKM8E1KGIksWRn4LpzBxUYZxWDBn6ILLLEu8mZ5kVt5q4RbKcbnbysLMKYKlhg1+W8w6shMBJmATXfhVeE39sfftTFpYYreR+NtsAqHq8MZpw6Za+67wiFTZfVFxnc9riQzs5HD1ydv8AF2tMVWzNnNLMUiFj8y3voETfjdFo/m7I2M30kAmwNZDCIsIVk8IYDFVkRYmUDn1Pt8SqXT4KmAzyNOR8YfYGNgazlyv4WWpJX6iDCRv8cXhVZIsRZHz/irRGoKztFSwELvvUQBevvceqWEkzwWH+2NbkZrT5SxMZJdTHCLp0+blDlO+DrCW4lP7HnO3sCINj7olcgB9XBfUFk7TcC2Av+wmmJQiVnbzPqlxbTN6s94E8pgImCYSkNpfpcE4CvDofsWcetz86pO259FzLN7hkiuET1/r3vny8/fnEO5nI45kK5mxm/La/Vbc5kw8ee8XQ1FwuIumDe4LkTGb6Gu0z7pkg96eSq+HpWwdNFX0uXNNg0hp9wvCiuDH0S0Kol1f0B5EKzkPJMRzdWD4zXLn7K3gP6+yaSxOfhB8ptMNNOVNdgAGizl08xpb/2pNR9gbmDKla67aRCk0RdAVXEuRP7FweYtyoNfc8qYevdRq5twtqsbVlMKBuveYnll49g4G5SuNmcXRi2rF15mMNR+r77UnGTLdVp0RpUfSWLXTnUkpUdBbAQClpbJNffYTRz4VBd3d5cGP0jzuVVvIE0PpKq+BPOnPwtyZFhpZHwfQZ5Sy+sRUyF0X4D8rFU9RPUIZ8+pXxEcQHhXbrKaTKcmATVXSV45XqnvsWVphA532ldlkfFHH99tSly2jYSchvIqH5ivIc4/G8Z6m/XE9gjlKAqy4lyzOV+3gfqfPpykUoDb6/4Qfe7LichhtyPY9Oqp8LdSD2U6P4pH7/xirvz4tosIrX8sVmuXHgQC9201WUlGsInNKvD6S/94MbKU8Hgbd1O35P+ucMNETnXTP/+yR8J7P73MkQDNBR8HLB0vWyFmGwLyNuawlCnJBfh+f1ahDMpi8zd5AP0A7MmdozXwp8cO+B0Vhpq87mNEaF0BE6NOA+x8oOS0qhN1Edqy9MwU3Qr22mNJanv06eCp6WsUyPQpSIojI+6KtkK4s3I6L8VYIvBG65+2OU/waIpX5LR4YCnvlPL//AHn9eL5EEesgKJd9MmaTFAA8+YrKi9irw0ygTwjKOHTRPuPihKhdncWrL3upYpzWkLwZO7hmM2Ybt3vZxpMDUq3GlTbTKba2KrlQ4JPQgcFJv944epxvCsYIe2FTOvUqypHvPm3eOjt3gtpwik9qPstqqZndfgLXIfVLpypuSRR3aD9SrNADaFTXC7sCzYfZsRhp8/o4yKM2yXDU3XSpindrpwb8bagaJ7+ehQBjyieXgQsScQIyKxuT8neJEYu97L2hNnyHVNjJJHzBLasW9s9Dc+olAHYz6clmxg7uEv5YJ6kFjFu5daXR1eOzvALJt2flHlGOGVTB6J2oK/cBUr8N9Owbj+9y6DEJ4hqROBBRlfVrlYzhb364+mbm6LNxOJ5LU5jmUcpCz3+NJ3diEz+rwX3qhM+DcxBmp4YDQsgg6/Reo4WM0oNa7RiC6zRiq2wRiu2wRjNa6VFWiNZpN9BmNyRGk0jHB8/SHWUsOkkeenWixE1pQNVJkpEsv+wmLWCmn+csFKZuI1nIvJ7t3x+HiZjxz9gMhrnGZNRQpUQ0dCHL1byFw38xaPRL65fD7yhvijmL1bwFwuNLwKfwk2giwe+dEnkj0v2DxEPb9Z0I4Sclio8M7Qyi5g1E/KSeQU+rdgmF72ayLAkpUonPWLnoD5Z8dczsMzvVG+h4qApNqcuNZuRgXeIfN8D8TVRmFGSIrdwhf+2+C0IblL62CkLOA3K2h5P1Ct0hfBE/VgVcht1fxxy0+M7SRcB5KMQI1y1nuUI40WRFZFzeKFuJ2A+G/jTkv3ypblD54fywLo7z231p+p2tc8BqPLWM3WCdHiVPrEK1TtEhOv/Juq/HaomfzZcdceIO4gK22JSu92fTu0di09gdx01PERsaENeg1BII8RsLNFtHcQz+0T+YfrjaEVUzb6nbOK7FnGXzfFu3uero9fEU3/uaGNJ5K9ZPNC4767sDtHqOKh5L/Dj3epx67zsVpVyyyzmWYhZrTADcMt8iAxhMzsvlJQCP6ax/1xibMq/Tx4mW/P1eGjIeLZKicfko2XKZlBr7uBANkf5l/MfNp9QYQybu/ium38l/4Kpks+Fo8b9g8Oh7U/0N3b2xPm/zf7SfABfaTyfzxxiPD/zqvGwgRiEGoQwOddkyeVGCJOwy47x5iuNEcLJBH3gHfMJOJU+EEpqHfkR+7NglbzWO5j90ZFjF+vKxiTocJrmJCrLYjqjxjkJOiPgF3ApHnghBfOrX4ZLwXQxqrsBFKa9Fuhb3v+N/kh+Vkqqyf4svlVvpRtPTaZhxLbDVyTESbTQxDDCzaF1B5QYVp4H+pm7SritNI4yBLpSrOArIGdhYTJAxXDxTlZKIIW8rlWapLqsZUARYPTxqlgfMQ1y3016HytXQRHyCodkPDJYBfLyoOr33KlXT+V0VYN45cBlii+9M0EBUq1q067igoNHqeCxMBzn3wNC4HIm5Is5ACLRZufb6hZFlDMOnYSXtMWbtToEHrTXAdXKun+mOR1pHH1389F3Nx99d9s052Zhwvnn2izcK6kr4CFnz2C+s9QiRsLHvBsf3WmFzOpuW8VFCDI1mCj36DRpqnBPC/6wJ1nJ+IgI0JxrkenrOxWTQ84ut3hXN3HFBbNAvpV6rJDNKDtDD8ixlivim1O3jlNmtPba25X3m3uFEqpMT4Lr0Qp9tDktWl0RAizWLUQens0vGWeXTZHlC1Z4tLqZePXcMRyVNxE2CL0wHyl+NOd6uTl8JhI8YAtWraeGnmQKaH2wiYWJKgg2VeWJUTHHZ+HQfeBHkCd+OosPXRopegU7QXkNWndlQLZ4gql/D9u2w2BeqyunNv258osXuYcjxfOMH5ybQ/zGjcU5oFmxOEW8OEVYHB8yQ7k2Y1VC+CxutryEcdaW0EGcJKrTYfBaxkKo2TNKsXSn/jrGZGh47LWHiTNTc8ZhmNo4mvh6oU3mIDf22hqOlqRUY6vksW7MZ5FKUfAgPiRqsNyijLhqsbRO6aYeUD/TPCWhEGZT/vE2BG/zjxV1uBUhNxaFvqZF9a4VztoK2GiHptFTjwihbnm6vj8iXuDFe4GDts/FZMrH56TQ6b6WJi9UtEg6bn+PQ/yf66R39EV+5WwwpPlVs5W59VqWa4ya8xQYhWrdhcIefMpiCgx3y1EfnaFOVAuftUR+/vUUmu7GUN0UTLe87yoWEQb3MufjTwvuVebaVCdHfpSeRlqoEObMWE/C6xlqRbW6ZRjBNxsNaOvkwx4dLVCrvRKrvRwOE4ElMnXAdzRP8+TnmxIAgaEgxPVeCRYYCggc2rgF9NhQ610rX9lkNNOnNxMYob5TEQWsbdyIzoPeAgnF1ODeHTzsbFpmmrnM3Jopo1gIMyEqsgf/xgWpr4QQgAa2AG94t2rObZpru7xx0wCC0blFjhvwTLi2mBVkeLebiZJpES5V/IDmbNe8h+UfNw6ao8JYgy3cIH/rOix3qW+fn5EKtUSHktw7qV2q9ajwnhDObUmuAzd5D9P3YfjBJME7QOGqYH7tn9+iBXczUGwXvbrNToGYu4Lo6d8CSVi+Y1Dc3yCaPKpN+Dgfu/98Nj75Q77xyTBiW2+78WKE3WImyauob8EmFcZs1K9Z9vnCchp32N5Wt1yf/V+rqBAZNOETAKr+FDG3KGwWc+cQKtF2scdKo8let52XzaL5MjSfJefDXF9R1Wi6yvXNqUrVFmRoc+nSopIzvbqKdoDg5Ad57f5HFTrM2+dfoXmf1bzr897xf1u0CreF6FMIGfg1ka2aV9JD2sQuKbNuNXYw70aCPDfNPEoTUhSuZytAu4RQMPQC9nGJ/GaQdjBXpU4b4If1bXUIH8+Gv3VzGAlcUI/K74nqlOAnQssBF9xQCO+kN5fm8zcM0/4M3jZjCcNVJJXAeQXRah65Gb5Ja02B64JPZZj8kwbO26rhwd+gD6bACJ682pvMmEb69FYcI4GpsnoDVkbRSNfsbnqGSJJfLDsLN7I03kMpcMJC7xCHZL3yXS1gfPW+vMoNT4jtDudWAmRHHZAbwhgRzbzNwWB9pN/RqsItEQs9F65RyabAxDd1n5KqTJN/hDrN1ig2m/aAc63m7FCbgj2ItiLE21EzV44haM4T9rqnYTxXVW2CoVo1/DTK5NoLZtOpWRBAUm+8a837g/mdENNpoUrGpfzrrPZXnkzpoOfH5UenPu06e2DOkz8I5leyevE+sXib47iCFjGLAWK/Y5aF+/84hPppA58m1XHmOI8FjwA1sW/HilkWMc+Kce/X5yDJWY0T1V+igkBxWTxLWDIaj/gXvKkwlUeU2jKJeWgGM3SttEz2lPdHguHk4A+rkzX+OPgbPvn9o3hOh+3WvdgODaibt5xecYmKvhNSbRGBXu32nPqbSUk7mBQwt5o72ONs0BJ46dg5QQyks9ENRANA/Me/RiKn9pkGLcvnX9Cy/Jyf09D/kd1tnFvcyt1m4NC3Dhp0KH2kcEmza4u7RB9+mfzzA/2RiksVl+CJpuoh6MtpyeWT3P5CC2olMBo4bvNio/oSgg9UTn8lDb3UfKTEqPt5qlss3qyDfDD/2fWgkkcwJVTHNtoLVtQdCtwuD+UyJ3GV4iQqIx2EH1n28MkMRoHh63Ja3PLzIjx6V3802rD1TZEf5SPMo4dOXrn3rj7CnG/MMDDnCOBwhH0ML8QEyx/9BJh1TeL7E3g/nd+v+yXeP2C8D0zgpy++jaeeaKnxKNWXpJAM8Uk4rp3r2fT2IfqINidNGQv1dYW6jnXKGFmMl/+4HmiCY4X7h9UsIMRQbZJz1vOJQ+cQa/gqkuiIBk2MU5qOMOhs23FKuw7HUWy0wecq0rIO6ERG1qlKMmjUivYTa5oUS+hqMc78y9UWdjNWvIuhaw739TtG12+TW9cl9i/5K/SvwmRAKJ+LVG+bszHCTMNtHLLJmr+M+vnYzf7rb846zZ7HMs1e9zXQ385GBJsIT6YLFlhOogvEcQ2Pzc+CIULdGfaKa7SwHHqL8G4VOOyJDNiueY8SutNcJ+RfGt4jRLVZ/qkBZPNmMQYkXpReWIv7zbH7zeeOezgoZYdxkmM+JhlzMOC4uPNG4tZb6MzkvULHm/2FfTTNjWBbnD0hZ0cJsfoyNAZEYDrP5hyuL25O3Q1//5zGnHF3sDPuTs3bpDn3SEtDIjmEFql4aKE1WfPuUHl05KehgSRQoEqn7tAL7wEB8qeLGmSODPxXgOErkErIKkKUiHfHXZq3iyimIkjJ11F9GJRIQ46qrjiOI4HKdHXzWCSPpScO4q5hf98MOTfar6NK7q/I39BcOHBviGqckkOhewE+RkBjMxuiLNANUahdOqTvIVQQ8q4t4XIwRYFT
*/