//
//  Copyright (c) 2018-2019, Cem Bassoy, cem.bassoy@gmail.com
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  Fraunhofer IOSB, Ettlingen, Germany
//

#ifndef BOOST_UBLAS_TENSOR_OPERATORS_COMPARISON_HPP
#define BOOST_UBLAS_TENSOR_OPERATORS_COMPARISON_HPP

#include <boost/numeric/ublas/tensor/expression.hpp>
#include <boost/numeric/ublas/tensor/expression_evaluation.hpp>
#include <type_traits>
#include <functional>

namespace boost::numeric::ublas {
template<class element_type, class storage_format, class storage_type>
class tensor;
}

namespace boost::numeric::ublas::detail {

template<class T, class F, class A, class BinaryPred>
bool compare(tensor<T,F,A> const& lhs, tensor<T,F,A> const& rhs, BinaryPred pred)
{

	if(lhs.extents() != rhs.extents()){
		if constexpr(!std::is_same<BinaryPred,std::equal_to<>>::value && !std::is_same<BinaryPred,std::not_equal_to<>>::value)
			throw std::runtime_error("Error in boost::numeric::ublas::detail::compare: cannot compare tensors with different shapes.");
		else
			return false;
	}

	if constexpr(std::is_same<BinaryPred,std::greater<>>::value || std::is_same<BinaryPred,std::less<>>::value)
		if(lhs.empty())
			return false;

	for(auto i = 0u; i < lhs.size(); ++i)
		if(!pred(lhs(i), rhs(i)))
			return false;
	return true;
}

template<class T, class F, class A, class UnaryPred>
bool compare(tensor<T,F,A> const& rhs, UnaryPred pred)
{
	for(auto i = 0u; i < rhs.size(); ++i)
		if(!pred(rhs(i)))
			return false;
	return true;
}


template<class T, class L, class R, class BinaryPred>
bool compare(tensor_expression<T,L> const& lhs, tensor_expression<T,R> const& rhs, BinaryPred pred)
{
	constexpr bool lhs_is_tensor = std::is_same<T,L>::value;
	constexpr bool rhs_is_tensor = std::is_same<T,R>::value;

	if constexpr (lhs_is_tensor && rhs_is_tensor)
		return compare(static_cast<T const&>( lhs ), static_cast<T const&>( rhs ), pred);
	else if constexpr (lhs_is_tensor && !rhs_is_tensor)
		return compare(static_cast<T const&>( lhs ), T( rhs ), pred);
	else if constexpr (!lhs_is_tensor && rhs_is_tensor)
		return compare(T( lhs ), static_cast<T const&>( rhs ), pred);
	else
		return compare(T( lhs ), T( rhs ), pred);

}

template<class T, class D, class UnaryPred>
bool compare(tensor_expression<T,D> const& expr, UnaryPred pred)
{
	if constexpr (std::is_same<T,D>::value)
		return compare(static_cast<T const&>( expr ), pred);
	else
		return compare(T( expr ), pred);
}

}


template<class T, class L, class R>
bool operator==( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs,
								 boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::compare( lhs, rhs, std::equal_to<>{} );
}
template<class T, class L, class R>
auto operator!=(boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs,
								boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::compare( lhs, rhs, std::not_equal_to<>{}  );
}
template<class T, class L, class R>
auto operator< ( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs,
								 boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::compare( lhs, rhs, std::less<>{} );
}
template<class T, class L, class R>
auto operator<=( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs,
								 boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::compare( lhs, rhs, std::less_equal<>{} );
}
template<class T, class L, class R>
auto operator> ( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs,
								 boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::compare( lhs, rhs, std::greater<>{} );
}
template<class T, class L, class R>
auto operator>=( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs,
								 boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::compare( lhs, rhs, std::greater_equal<>{} );
}





template<class T, class D>
bool operator==( typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,D> const& rhs) {
	return boost::numeric::ublas::detail::compare( rhs, [lhs](auto const& r){ return lhs == r; } );
}
template<class T, class D>
auto operator!=( typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,D> const& rhs) {
	return boost::numeric::ublas::detail::compare( rhs, [lhs](auto const& r){ return lhs != r; } );
}
template<class T, class D>
auto operator< ( typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,D> const& rhs) {
	return boost::numeric::ublas::detail::compare( rhs, [lhs](auto const& r){ return lhs <  r; } );
}
template<class T, class D>
auto operator<=( typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,D> const& rhs) {
	return boost::numeric::ublas::detail::compare( rhs, [lhs](auto const& r){ return lhs <= r; } );
}
template<class T, class D>
auto operator> ( typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,D> const& rhs) {
	return boost::numeric::ublas::detail::compare( rhs, [lhs](auto const& r){ return lhs >  r; } );
}
template<class T, class D>
auto operator>=( typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,D> const& rhs) {
	return boost::numeric::ublas::detail::compare( rhs, [lhs](auto const& r){ return lhs >= r; } );
}



template<class T, class D>
bool operator==( boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::compare( lhs, [rhs](auto const& l){ return l == rhs; } );
}
template<class T, class D>
auto operator!=( boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::compare( lhs, [rhs](auto const& l){ return l != rhs; } );
}
template<class T, class D>
auto operator< ( boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::compare( lhs, [rhs](auto const& l){ return l <  rhs; } );
}
template<class T, class D>
auto operator<=( boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::compare( lhs, [rhs](auto const& l){ return l <= rhs; } );
}
template<class T, class D>
auto operator> ( boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::compare( lhs, [rhs](auto const& l){ return l >  rhs; } );
}
template<class T, class D>
auto operator>=( boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::compare( lhs, [rhs](auto const& l){ return l >= rhs; } );
}


#endif

/* operators_comparison.hpp
BeQCWW1ljyvda5Lcf1WmkLsuTgSzWQlEHaHbCVi781OirOJ3p8JR4RL6LtznCBDdYgJMkRjIYT7xX8X2r/CkjQzjxi+F8pZp+r3q98i/1NzIECwEn+404sar5+PF6ZIITX6IMXHzDqCmFk+P1/loJqa3xARCmRoxHoBcOYCVWGh5V3d405182uyFO3Iob7W+YLoD8d0F48XV4XYora6dyTHHnskoSaGZTwzWcgdH5S48wRySUM0TFk/r0UT5E6unQs0JGRT/6JY71NkUCTKz5WTR6uqXCjjnrZ7aSpCfQR7Nl+zU1jcqIIl/TSmwKKQkjaTLBOTKmhFHtnqUWeyoEHCT+J7V96OLr1TjgzkqZQnGXNy4PNnb7fUZif/M0KSsbqelt6TKudXHRc/UJSkKPa+xnm250rtMTepZhA7Pe4hjjI2upg/yQDycKrrB73MKXe2u+WFuy6ApNSz9PcsBB9iTLIZ7b7HeFzT53wkIZ3YFXJbeT89zw7IcjZyZA91BhlXjulJOcNF/4ZZf0KH7ZPe7f0U312cRO/1XnaO0L3rxD9QuC/JX/wpJrYHnkpjOV4bqTzakZfzABXwUkzmfWXqY+BIWvV4lHZJr/iJ9i8svMkQ+Pt1Vv114vGCYRaZBf0aHMeLUrOeVtvbu6mNcNurKi/i3zprzr9vMN3+Ui0ic0hQWo/YqOQKxpakwYQmcZ5x99Issm4758Zmhfr1Fg7SYLGrSVSbafObOTDzvY81u0iK/p4ZwSjWtDVLiBaYmMNUANRtLb4ZsACL6XqfCGcFsi2guAiz6oJyEBA8Cgj311pv5nGGR35E0qBRcgq1lHr92XkGhvNWnNruhj1Ibrd0dHavHDJ9SeT+eQjWpLnWN/mBUJZDxXK/v7sLtSrBoPJ2d49E9uyn/kGSLUwo9hNnneIWpifrHh34ys1pYzT/URdwmv5AHcysjOh8on6y/NM8cDCEXw5behDoVK/vZbCOWZzpSUkGhrx4Xr9OHJe8IyavwriqyPzM5h87VZSomP6hOmpibzhCxGzAdFxZFy3xUpq1Dtwv47JcQoje6U08Rfi9kN54D9zx+mxpLFfK1vuizO5u/nSxJRDsKArJnufKBoyfZiugQuSAo8Z8/7hj//9yqlpr6LrVY9s7oEaNvsSTj1srK1LVz/q/iHc4d+WjGvyKsysrKqsqk0iLU0JSYIsYY7nJs9JQ/27R+r7mlsFIV5sCnYrjujpQM5SSnvH2Qs7ntfvKc5vGdbvuOP+m/er/U+97k3r663mz73vCcfurm4XdBdO35wj9FuXP0UeSkYP19w0FblNcsrDdH4nwu2GlTWFrjQnXUzM3OhHVDXmA0tDSJp5GiRTt07Dk6v2g3OyfFB3MHi9Qp34v3lc6ZIW4JQrDKfj0v+ATrksQ86Cd0A9CQY/1XPjpsRyH09VarVc6hlJrawzR0bAzUnRXaJa9uVARrGDZWIZbGjRzat016qPCWXq0hcw57TgowkVwPL4Hog7mL5555tMZv/8Notj00P4o0iFzn+nQXPpge6FS50g58wWOfnnq+k238eeMXg811FWjbeo/mUNFeMurpHelfvsU8ymwOVoT6U7Em9WWPo+EtyoFDLH3xYi0WL+TCPXF0KJ8FrzoFW+9V96ft/URrl9cRvt0Ze5FpUIeGscxu+defmF8zAZbP5p6Y7TI4/PVBdMRqxasTl7PPE/7O+3XgrwK2iECjNmFBA9PznUFvjb14/YpWtvhlOBeeeSwfc0rivVNNk2n92A/D6lG/VkaNvTomm7aqCJDSEJuwuTzd39TBdfAXUiNFXcZ4w6RkNbMkXsTpOzIW82Dr/QthgZoOiuYPbSUKREgA8kKE7VNrCVfpawZU7F67ygStB2yGv5FgEvNIP0dSJOrpkVpO+18E+cGpmix91NoKBmqn5Lm3mE9D83EClZC3068BwNYNkxkeXa0Xhi1HUthwKZ8t6eSw49scg8X7XinfMEQAK4puMooRyJDy0rWlSGO2R1myLypRzo3xqMKvkNRL7u+vumUE19gnxEZPnPu9MIaoQjMCcflgoYNVfOdLoVqOKC57skTWrvJ12b4FHH6G1zJDa6D2wfYg0pDoopGF7rgPKw32SyLKP1DLIkMghmCJwlL0EXQfekbWoJol18ShgQtb44RjmnfbJMWxyiy8ls/rMGiW6Xkv1VX8TsJSrGiQpThqJONrjtvcqJoDCpBWtBfnkSuo9lB9Bt7ls5A7lXxTH65lA38sXuHOkw/Vb4h8vhTy1e9dFdApMlNf3kV6DatNnHB8dP7KjOTH9pKFgawHNwbFgnz4ptILe7CpaZVW8d55HLx55QjmDHaU7k31Hg/l7Zics1sjpeB4kqJoe7wk8c6BdfBv5VPdmDVv5eCmCjhhU7mwr5HzX6MMFi23dIoK1qnR4PuPZ2LXsLdQHeOnNYMVjT2b5spDoRJlR7QM/ZTZ8eVwOzuPe6HxOpbMfLrIY/6Xw2eKIygGzNaR8z2mCOcxcwRHkPZAmH/MFwp9QuCx5eVS5uwvea5KVAc29p5exLqXjsHMaXlgffrvvP0Pl5VVW0hJJG4iXYeFdPrPSlP810rpMBNoVoaUnJ22eE1YQg7RU9dVyIw0xTvA6dkLOZYnqTtCo8b5UVYaQ0XCQDOj5Na8zJ5QPQhu6PfPkyOcy3wKQaVZAgZyVP720z6BAMa5uSN2LbAaMiOBvOGLiOe0t1PDEOLsYaE//ahf9hs2AXNbN0qvtoZPWIkfwJncHF34v5UaIpt5syB1k6kr6QpPgj/CFHuF5iYdGG6ZvoOm0PNDdrnAHu2G8pJfUh+8M4WyA+cwpwV2ynl0JFHtw/pswReqBhWFZf8VT2WP/Yel3zw6r+dO0Z4LJEHwajJLynsSRT2XKPyAf7JKRp6a73yZA3fELZxlI4q2d2HQJp2HiFp5nXO20KrZz1X/aekSmxlc4gTH6QubIsTtndmwh3jGPlkUxxBna+ASayecBbNKaHTdO1OAMjDRr1UX+2VZ05UIIvlfSyWb69QzX6Tt8ILWRiduXX4C67Ut3pX+vVTB7NvXLHrzdw3gQ+/GMBjsyRcoVi1uQDwK5yN/nDHQ5cOW3AaqirmInEfe6P4FDJbW9gh61hf6bryqGBiI9w/kep6zOfu/sLXQRGC0Pcu6v0cyUtQZZzMBkZbhCvL6lkf2VpKUmUaqJ8BLqfjyWIXpIXTSS6keK0N+a2CpBNbdtVIut8967PtrR6HeN52A4GokjAh1im6EGEYkVPfbE1Lc9JWkTKnGxAkPDNOtHo2Joj5rMk4ILwIKkuo0UZ+0JERt1nkteAbkA8+ffBsab43lyxr+MwfnBV9QZEy8vpzy6w/4sQsr4UPBg35xgEuAP6/0C7vxq/g/omG+y4fGZ2grXOF5RqyD415zdX6Dl3nq3JTns1zdLwu+uQK4DFahgK4fslPlDYGMWA/TaLpgoBFshY0/b+53/Mh599GZQn1sBjfLO+1Iv6NIfOwatXvzJYeX3792+bwpZVQApaoaH0BwEnGwzrsmMxA59ON0ZadQoOB0SL5Y/B+3OLNdP8QgFrZool4LeILr/yh4TDrr9SK/FiKUQQ/Hl9vxb3X9ibYGvXp03aZpxud4unmXG3/DsnHgUSyNDEaJ9bNpZ04VTLz7Q73L63mnVmGYrUHOlO4rXzdxdO+qLZAl86jQZlZlnKCUr9hZoYmRhgLzejwsJjPVSEp5wSyY6NDeWYuKOVBpduEHODf6AAAs/9MANrb0Zy6LihG95fMYTEOAlcsYn7UQViGxXb0U7zV1Dr+i91BsE2Z4FjXhZsBTq1/i5Nfq1pifXffSIRWaSDw0RQ4REnJz1up/XfVJAt0s2ZjWN1UfY/ulwTM4KVc6P7p4n9Kx7zYazcFb3J7XQYzLX/QVlvspP9P38qA9jR8QQSPHKwHjEIMEKhAFeGCUTBxjt5KpTe/Tm9KvyKoDq/Bte8yIy8yku53Hdn3Ffv9G2DW5FCWD6/eU10Fscl+2PZTqwIKu0bb3DN+Bbq6Quj0sFR0Vyvp7gwVu4Ueb8MnPuJLXU0r/07Rpcceb7GmqnO7zv9WjyFK4GEzlqdN/4dkXdOl9fGmGzUCLcgwdQqyBIWynHcNScmHZEmyA9XuYU4+ZJWzDIZ8n3CfD8w8/L2jdqqM3pJln46PpWgdvmF2YmNiBjFyiu/gf5KjWVwDtWWcD6LgHnfnSC4PL3/vvQa+XbjyBrzDthgHRAJHNd5wLEOPCxh7/SJtzBIOjtrDAz2ViRhZc5lLHLkCTfq2yFWx3QPJmkQrbIAwq+Ku3UP/8NsPRKbrfXDeZ/t62ZwqzNHDUafMD0KpgbiIoVmEN6nnsWJsb9I4keyIDHfrlMUePEK7egoQxoavOH+XzHB0T8+pABYrQANNH+T7mW7s2oepsfYVrD2hapg1dKrQvzH3QPaVpH4OK8DvHHgYKbinYttJB+WUFLliu5KgeTSII9rnfYPGEGftea99TRQSv3cTC8ye1gGcCPMILgrnGXoVuZWb5zBvEsl1q8ckDLS+efklR9JahyrH8gV/j9rJhGaXWiac16EEVL4c96Kyp8SNnztDqPROE2icZ0AorvANzkcq5Gkgb9VGSAewPjd9gRR4fZKp2XI1QZ9HpnFC9YFZcPjgjA/CIc9CULBJKWw8xeUP4yL4RvN/a6/SpHUgX3iZ3qE4dC6MxyR7DmJEQbySQqYFQGawcxNoM2llRmaMUjVW9GATSzuXKOiNdjGLlu9yxFz/8aR+CjYwWXW01IbQR6kVm9hCItsgrf7bF0yteLOr18hs/8XAuD/2qPsbmMORdjUY5EU4QDZw+uVhD2LLXnVnTZUDzNrraBnv3ZFoxhP1skhNYQCTnndEaOeXFG1P5YTzo0Zew0dvM2r+fZyjPvjSfGxB8S68qfRwkSmfXs9KWac8rpBFIwerYZD9/hqzr9h4IRuwD8R64GAN0mvpKnxnquEjKJDgsHA9iTL8qwo65jzYeZJ84p8TVQpjvjWTkuDH1tTHq7UX2LgNKPFWDmFDDTkCDQmeAsAcUnZOKdw0jftDg8HFS76d71Ro97Z0r7Liv67rfCSX0Z3Rmj1R8LAWqdj4mAaOCpM0adCdRCePHg1mRKwovaJrAuP8yu3KKvpro1Cco4OgSITVAXeKeyJLtP9+yPiDxHW9+6JeQ7iO1hlMelpMBwv4RseUH1KkEJ8tO+8XRw5h2RsCfdu82JUUmGyrCQLN9OU4UyUVT/4HoynQvkYYrvHqv2R5sB4hGjBWneYY+H48h4ovdH5970X5+23reABh8LrX9NlqvvHkQB95t/yoLe3WMVPi/R9mjfmlUADteTV+3kNFee/zVzrjgRvHKqBpmup9Nt93B2Y8UiwKCHPH+V4bQ6qQa19QA7kZq4oOhWrW+d62kBtp3briQM3poMs+0Sn9qhfOcOb5oGwidQPe+xhAerBkxbdDU6y6vPGB3L+boUoqXJzDG/2i8/FzwwfKPElhog3YPkTbFWn5J8pSpnPKDO7hqSs499jRfh+GffvCvVuZtP//UjbaP8PCWe/L+wjFQvAA/iRSsDSmn4d8Ao7rUwk1mIWtb29YWoF0u+PxLfapldlLNjWampfV8M45hZskhuGDfppVaJJ65kGM4S58FWIkk+hHIrPgr3pmtPlA4/vkqqlfuHU9S1IDGctX6wq8TQJO9IxQYNntjqE+7ugISEeJ8Us2lOKl/eUXs5UoYbUmhjHXIF7ONcWPYKbfIujGV05Op+sBelPLWqbtZg32ZgnScdVvm+B1IPgLMkjI759z4Sv4xpaEkmGCWcGrTYWvQrAR7WiebDVDjfAX818adhfAMCkpzgX8GWWT51T9TVDUk1FneHIjyEFWwKnsxSqIVGsLEmJZlgooLgX86QRJERn5BUXnSh5OumxCrbT0k9hELu7+3+vaKc4lD+waeePG9ZLdY7ti2zga6eeXfIk7LSFUO8K9AFjiX6DbqlkSfOwasiLG8IpHoy1tBzmAWJ4jsn9lBkoD79FfVezIH1lF8yB7effdMYxXDZj4MEmt8I+zngPj+qaTlAnnkPA0of19LJbldKFkrxroPO0q0Rir7NRZ32MypVwTq8gNV/tiP8aX3gMHfdYO+O+Aq9FJLZdNAKQoTlc69HqZtMhZG6CVhJENE2F8aw5zIbM2b9r1Bl9B1zH/388V08kvmOkZ4B0sfA/Mg1uCJn/qjNgPmZfkVsaLgR6lc2vOcsXGKB6xkOSbr6QKJf6i3J9QTOzW25zFj47pNlPtvStNe/fLM6WM5I4aQCD8+BmA7YR0qoeq3y/z8dw1ZKsl4TZ7C3nQMns4QrO9DZIoYaLTG8ejzw0Icx58q2Bk3gRf9qD+XavxWb6ktDYaTfv1DMfn4lbf6Vhl7ay8liX7ORGfx8czBg184HvooJZlWQ+GK1qJwoJCJEejp2Vj4MWl/Nhu1y6/6/PJM4tzxnJxYhMBwWSZz2P1Ha3f5PTFFAcsidW0AB8h4EahoX5rdlLPGutclLZr1s/3PO6c52xq7AvQSCctzVpUvsYPKHYwr/kS5JMpk4Th8knS8gomvWEPnsCKf6HAvYcf7gABH2Nrlv2dN3c2l8+t0YvWqyTyxo+2Vt/sBxvSjnfVdaadmyP0hWgYhZPkv5e0aKZC2uYtHLFuafvEZbGFLrqTUTCLcnCdaAvUI4xEMq+PWNVOhPmlLrmg3EM8+iadum1lscXoJKb23hfAFv+Uy9JKr3L4HWr3qM/2My8b+17FzN27hlU3MPBuuA//FpTV1Xx49WeSDz2KYgT1El+7ZCqkeM2AwoY4zkVLBmeJO3Fwcgs2Kgxx0bJb8zEBQrX6/GUTTR/bEII5TR/obnJToR3+GXVk83krELQp6qDeLpEd4yT9ewsDxFnXsqKrai6qmpPaH9bb73MfRB7X3SSgcygXvXYrl11nsCy6e0G0lb1GHCoKjcB3CNsV3Kvgjl3juXhts4Soeab7E397McfRjJRyy2jKVE3Bfk/wx2ZdfuS6ultQuIOQAsdmWn55TYhzjyJzH7+Mvb9fasxwevguo1GorPF+leJHUxAhWQ5pv6207Annz9HzjpvFRAafyy7OaCge6hhNP7jUKYdqkH52Ho1+eYPSQ6yHo8gBd8q7Klws1tJesuc9KlAz8wS99iFhPFx3/ceR+yqsoawD+9dzWmPEsiOhlHqoq/hneg7begVFpB8R/GNoQLAOGCCXsI2pLUiPV9FFPPG6YQLgsXUCUNXBkqFA/auck0UEfu4ZjOtgBF+NJGXmpmPbItrsX9ql/YahH4Ju5yt0vZ6jc7jwUggQrwcgimPsz8ha+LD4F+PDX660vRxy4BefiN4A8pyHc5hD6r2ToCLwHbR4kSRQEA07jA7ED2grNUee3EUTIA/tDYDjK3VsVtoNwmMIFMdm4AQHSre2vO2MmBuTi1Af2H2T5G9fcFSjEi7sos6TGrV2jNKkc5WhKj+HeenMeYsYdvyqBdWANxBLV59c3HZj3QOE6sgbM6aOOk0REcb1rFrxYKSs5IhVsXhtnCJXXYJzMa7TV9psyED9iOekMvv/lFuNXThEi+Y0I34N/AWv8nJp7clB6Bby7wRkEFLohPvCDB3ah9t9iTwH8jSJ6
*/