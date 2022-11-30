//
// experimental/promise.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2021-2022 Klemens D. Morgenstern
//                         (klemens dot morgenstern at gmx dot net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_PROMISE_HPP
#define BOOST_ASIO_EXPERIMENTAL_PROMISE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/cancellation_signal.hpp>
#include <boost/asio/experimental/detail/completion_handler_erasure.hpp>
#include <boost/asio/experimental/impl/promise.hpp>
#include <boost/asio/post.hpp>

#include <algorithm>
#include <variant>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {

template <typename Executor = any_io_executor>
struct use_promise_t {};

constexpr use_promise_t<> use_promise;

template <typename T>
struct is_promise : std::false_type {};

template <typename ... Ts>
struct is_promise<promise<Ts...>> : std::true_type {};

template <typename T>
constexpr bool is_promise_v = is_promise<T>::value;

template <typename T>
concept is_promise_c = is_promise_v<std::remove_reference_t<T>>;

template <typename ... Ts>
struct promise_value_type
{
  using type = std::tuple<Ts...>;
};

template <typename T>
struct promise_value_type<T>
{
  using type = T;
};

template <>
struct promise_value_type<>
{
  using type = std::monostate;
};

#if defined(GENERATING_DOCUMENTATION)
/// The primary template is not defined.
template<typename Signature = void(), typename Executor = any_io_executor>
struct promise
{
};
#endif // defined(GENERATING_DOCUMENTATION)

template <typename ... Ts, typename Executor>
struct promise<void(Ts...), Executor>
{
  using value_type = typename promise_value_type<Ts...>::type;
  using tuple_type = std::tuple<Ts...>;
  using executor_type = Executor;

  executor_type get_executor() const
  {
    if (impl_)
      return impl_->executor;
    else
      return {};
  }

  void cancel(cancellation_type level = cancellation_type::all)
  {
    if (impl_ && !impl_->done)
    {
      boost::asio::dispatch(impl_->executor,
          [level, impl = impl_]{impl->cancel.emit(level);});
    }
  }

  bool complete() const noexcept
  {
    return impl_ && impl_->done;
  }

  template <typename CompletionToken>
  auto async_wait(CompletionToken&& token)
  {
    assert(impl_);

    return async_initiate<CompletionToken, void(Ts...)>(
        initiate_async_wait{impl_}, token);
  }

  promise() = delete;
  promise(const promise& ) = delete;
  promise(promise&& ) noexcept = default;

  ~promise() { cancel(); }

  template <execution::executor Executor1, is_promise_c ... Ps>
  static auto race(Executor1 exec, Ps ... ps)
    -> promise<void(std::variant<typename Ps::value_type...>), Executor1>
  {
    using var_t = std::variant<typename Ps::value_type...>;
    using pi = detail::promise_impl<void(var_t), Executor1>;

    struct impl_t : pi
    {
      impl_t(Executor1 exec, Ps&& ... ps)
        : pi(std::move(exec)),
          tup(std::move(ps)...)
      {
        this->slot.template emplace<cancel_handler>(this);
      }

      struct cancel_handler
      {
        impl_t* self;

        cancel_handler(impl_t* self)
          : self(self)
        {
        }

        void operator()(cancellation_type ct)
        {
          [ct, s=self]<std::size_t... Idx>(std::index_sequence<Idx...>)
          {
            (std::get<Idx>(s->tup).cancel(ct), ... );
          }(std::make_index_sequence<sizeof...(Ps)>{});
        }
      };

      std::tuple<std::remove_reference_t<Ps>...> tup;
      cancellation_slot slot{this->cancel.slot()};
    };

    auto impl = std::allocate_shared<impl_t>(
        get_associated_allocator(exec), exec, std::move(ps)...);

    impl->executor = exec;

    [impl, exec]<std::size_t... Idx>(std::index_sequence<Idx...>)
    {
      auto step =
        [&]<std::size_t I>(std::integral_constant<std::size_t, I>)
        {
          return [impl]<typename... Args > (Args&& ... args)
          {
            if (impl->done)
              return;
            impl->result = var_t(std::in_place_index<I>,
                std::forward<Args>(args)...);
            impl->done = true;
            if (auto f = std::exchange(impl->completion, nullptr); !!f)
              std::apply(std::move(f), std::move(*impl->result));

            auto cancel =
              [&]<std::size_t Id>(std::integral_constant<std::size_t, Id>)
              {
                if constexpr (I != Id)
                  get<I>(impl->tup).cancel();
              };

            (cancel(std::integral_constant<std::size_t, Idx>{}), ...);
          };
        };

      (
        std::get<Idx>(impl->tup).async_wait(
          bind_executor(exec,
            step(std::integral_constant<std::size_t, Idx>{}))),
        ...
      );
    }(std::make_index_sequence<sizeof...(Ps)>{});

    return {impl};
  }

  template <execution::executor Executor1, is_promise_c ... Ps>
  static auto all(Executor1 exec, Ps ... ps)
    -> promise<void(typename Ps::value_type...), Executor1>
  {
    using pi = detail::promise_impl<
        void(typename Ps::value_type...), Executor1>;

    struct impl_t : pi
    {
      impl_t(Executor1 exec, Ps&& ... ps)
        : pi(std::move(exec)),
          tup(std::move(ps)...)
      {
        this->slot.template emplace<cancel_handler>(this);
      }

      struct cancel_handler
      {
        impl_t* self;

        cancel_handler(impl_t* self)
          : self(self)
        {
        }

        void operator()(cancellation_type level)
        {
          [level, s=self]<std::size_t... Idx>(std::index_sequence<Idx...>)
          {
            (std::get<Idx>(s->tup).cancel(level), ... );
          }(std::make_index_sequence<sizeof...(Ps)>{});
        }
      };

      std::tuple<std::remove_reference_t<Ps>...> tup;
      std::tuple<std::optional<typename Ps::value_type>...> partial_result;
      cancellation_slot slot{this->cancel.slot()};
    };

    auto impl = std::allocate_shared<impl_t>(
        get_associated_allocator(exec), exec, std::move(ps)...);
    impl->executor = exec;

    [impl, exec]<std::size_t... Idx>(std::index_sequence<Idx...>)
    {
      auto step =
        [&]<std::size_t I>(std::integral_constant<std::size_t, I>)
        {
          return [impl]<typename... Args>(Args&& ... args)
          {
            std::get<I>(impl->partial_result).emplace(
                std::forward<Args>(args)...);
            if ((std::get<Idx>(impl->partial_result) && ...)) // we're done.
            {
              impl->result = {*std::get<Idx>(impl->partial_result)...};

              impl->done = true;
              if (auto f = std::exchange(impl->completion, nullptr); !!f)
                std::apply(std::move(f), std::move(*impl->result));
            }
          };
        };

      (
        std::get<Idx>(impl->tup).async_wait(
          bind_executor(exec,
            step(std::integral_constant<std::size_t, Idx>{}))),
        ...
      );
    }(std::make_index_sequence<sizeof...(Ps)>{});

    return {impl};
  }

  template <is_promise_c ... Ps>
  static auto race(Ps  ... ps)
  {
    auto exec = get<0>(std::tie(ps...)).get_executor();
    return race(std::move(exec), std::move(ps)...);
  }

  template <is_promise_c ... Ps>
  static auto all(Ps ... ps)
  {
    auto exec = get<0>(std::tie(ps...)).get_executor();
    return all(std::move(exec), std::move(ps)...);
  }

  template <execution::executor Executor1, typename Range>
#if !defined(GENERATING_DOCUMENTATION)
    requires requires (Range r)
    {
      {*std::begin(r)} -> is_promise_c;
      {*std::  end(r)} -> is_promise_c;
    }
#endif // !defined(GENERATING_DOCUMENTATION)
  static auto race(Executor1 exec, Range range)
  {
    using var_t = typename std::decay_t<
        decltype(*std::begin(range))>::value_type;
    using signature_type = std::conditional_t<
        std::is_same_v<var_t, std::monostate>,
        void(std::size_t),
        void(std::size_t, var_t)>;
    using pi = detail::promise_impl<signature_type, Executor1>;
    using promise_t = promise<signature_type, Executor1>;

    struct impl_t : pi
    {
      impl_t(Executor1 exec, Range&& range)
        : pi(std::move(exec)),
          range(std::move(range))
      {
        this->slot.template emplace<cancel_handler>(this);
      }

      struct cancel_handler
      {
        impl_t* self;

        cancel_handler(impl_t* self)
          : self(self)
        {
        }

        void operator()(boost::asio::cancellation_type ct)
        {
          for (auto& r : self->range)
            r.cancel(ct);
        }
      };

      Range range;
      cancellation_slot slot{this->cancel.slot()};
    };

    const auto size = std::distance(std::begin(range), std::end(range));
    auto impl =  std::allocate_shared<impl_t>(
        get_associated_allocator(exec), exec, std::move(range));
    impl->executor = exec;

    if (size == 0u)
    {
      if constexpr (std::is_same_v<var_t, std::monostate>)
        impl->result = {-1};
      else
        impl->result = {-1, var_t{}};

      impl->done = true;
      if (auto f = std::exchange(impl->completion, nullptr); !!f)
      {
        boost::asio::post(exec,
            [impl, f = std::move(f)]() mutable
            {
              std::apply(std::move(f), std::move(*impl->result));
            });
      }
      return promise_t{impl};
    }
    auto idx = 0u;
    for (auto& val : impl->range)
    {
      val.async_wait(
          bind_executor(exec,
            [idx, impl]<typename... Args>(Args&&... args)
            {
              if (impl->done)
                return;
              if constexpr (std::is_same_v<var_t, std::monostate>)
                impl->result = idx;
              else
                impl->result = std::make_tuple(idx,
                    var_t(std::forward<Args>(args)...));
              impl->done = true;
              if (auto f = std::exchange(impl->completion, nullptr); !!f)
                std::apply(std::move(f), std::move(*impl->result));

              auto jdx = 0u;

              for (auto &tc : impl->range)
                if (jdx++ != idx)
                  tc.cancel();
            }));
      idx++;
    }
    return promise_t{impl};
  }


  template <execution::executor Executor1, typename Range>
#if !defined(GENERATING_DOCUMENTATION)
    requires requires (Range r)
    {
      {*std::begin(r)} -> is_promise_c;
      {*std::  end(r)} -> is_promise_c;
    }
#endif // !defined(GENERATING_DOCUMENTATION)
  static auto all(Executor1 exec, Range  range)
    -> promise<
        void(
          std::vector<
            typename std::decay_t<
              decltype(*std::begin(range))
            >::value_type
          >
        ), Executor1>
  {
    using var_t = typename std::decay_t<
      decltype(*std::begin(range))>::value_type;
    using pi = detail::promise_impl<void(std::vector<var_t>), Executor1>;

    struct impl_t : pi
    {
      impl_t(Executor1 exec, Range&& range)
        : pi(std::move(exec)),
          range(std::move(range))
      {
        this->slot.template emplace<cancel_handler>(this);
      }

      struct cancel_handler
      {
        impl_t* self;

        cancel_handler(impl_t* self)
          : self(self)
        {
        }

        void operator()(cancellation_type ct)
        {
          for (auto& r : self->range)
            r.cancel(ct);
        }
      };

      Range range;
      std::vector<std::optional<var_t>> partial_result;
      cancellation_slot slot{this->cancel.slot()};
    };

    const auto size = std::distance(std::begin(range), std::end(range));
    auto impl =  std::allocate_shared<impl_t>(
        get_associated_allocator(exec), exec, std::move(range));
    impl->executor = exec;
    impl->partial_result.resize(size);

    if (size == 0u)
    {
      impl->result.emplace();
      impl->done = true;
      if (auto f = std::exchange(impl->completion, nullptr); !!f)
        boost::asio::post(exec, [impl, f = std::move(f)]() mutable
            {
              std::apply(std::move(f), std::move(*impl->result));
            });
      return {impl};
    }
    auto idx = 0u;
    for (auto& val : impl->range) {
      val.async_wait(bind_executor(
          exec,
          [idx, impl]<typename... Args>(Args&&... args) {

            impl->partial_result[idx].emplace(std::forward<Args>(args)...);
            if (std::all_of(impl->partial_result.begin(),
                  impl->partial_result.end(),
                  [](auto &opt) {return opt.has_value();}))
            {
              impl->result.emplace();
              get<0>(*impl->result).reserve(impl->partial_result.size());
              for (auto& p : impl->partial_result)
                get<0>(*impl->result).push_back(std::move(*p));

              impl->done = true;
              if (auto f = std::exchange(impl->completion, nullptr); !!f)
                std::apply(std::move(f), std::move(*impl->result));
            }

          }));
      idx++;
    }
    return {impl};
  }

  template <typename Range>
#if !defined(GENERATING_DOCUMENTATION)
    requires requires (Range r)
    {
      {*std::begin(r)} -> is_promise_c;
      {*std::  end(r)} -> is_promise_c;
    }
#endif // !defined(GENERATING_DOCUMENTATION)
  static auto race(Range range)
  {
    if (std::begin(range) == std::end(range))
      throw std::logic_error(
          "Can't use race on an empty range with deduced executor");
    else
    {
      auto ex = std::begin(range)->get_executor();
      return race(ex, std::move(range));
    }
  }

  template <typename Range>
#if !defined(GENERATING_DOCUMENTATION)
    requires requires (Range&& r)
    {
      {*std::begin(r)} -> is_promise_c;
      {*std::  end(r)} -> is_promise_c;
    }
#endif // !defined(GENERATING_DOCUMENTATION)
  static auto all(Range range)
  {
    if (std::begin(range) == std::end(range))
      throw std::logic_error(
          "Can't use all on an empty range with deduced executor");
    else
    {
      auto ex = std::begin(range)->get_executor();
      return all(ex, std::move(range));
    }
  }

private:
#if !defined(GENERATING_DOCUMENTATION)
  template <typename, typename> friend struct promise;
  friend struct detail::promise_handler<void(Ts...)>;
#endif // !defined(GENERATING_DOCUMENTATION)

  std::shared_ptr<detail::promise_impl<void(Ts...), Executor>> impl_;
  promise(std::shared_ptr<detail::promise_impl<void(Ts...), Executor>> impl)
    : impl_(impl)
  {
  }

  struct initiate_async_wait
  {
    std::shared_ptr<detail::promise_impl<void(Ts...), Executor>> self_;

    template <typename WaitHandler>
    void operator()(WaitHandler&& handler) const
    {
      const auto exec = get_associated_executor(handler, self_->executor);
      auto cancel = get_associated_cancellation_slot(handler);
      if (self_->done)
      {
        boost::asio::post(exec,
            [self = self_, h = std::forward<WaitHandler>(handler)]() mutable
            {
              std::apply(std::forward<WaitHandler>(h),
                  std::move(*self->result));
            });
      }
      else
      {
        if (cancel.is_connected())
        {
          struct cancel_handler
          {
            std::weak_ptr<detail::promise_impl<void(Ts...), Executor>> self;

            cancel_handler(
                std::weak_ptr<detail::promise_impl<void(Ts...), Executor>> self)
              : self(std::move(self))
            {
            }

            void operator()(cancellation_type level) const
            {
              if (auto p = self.lock(); p != nullptr)
                p->cancel.emit(level);

            }
          };

          cancel.template emplace<cancel_handler>(self_);
        }

        self_->completion = {exec, std::forward<WaitHandler>(handler)};
      }
    }
  };
};

} // namespace experimental

#if !defined(GENERATING_DOCUMENTATION)

template <typename Executor, typename R, typename... Args>
struct async_result<experimental::use_promise_t<Executor>, R(Args...)>
{
  using handler_type = experimental::detail::promise_handler<
    void(typename decay<Args>::type...), Executor>;

  template <typename Initiation, typename... InitArgs>
  static auto initiate(Initiation initiation,
      experimental::use_promise_t<Executor>, InitArgs... args)
    -> typename handler_type::promise_type
  {
    handler_type ht{get_associated_executor(initiation)};
    std::move(initiation)(ht, std::move(args)...);
    return ht.make_promise();
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_PROMISE_HPP

/* promise.hpp
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
*/