#ifndef YU_SELECT_DETAIL_SELECTION_INVOKER_HPP_
#define YU_SELECT_DETAIL_SELECTION_INVOKER_HPP_

#include "capture_type.hpp"
#include "perform_selection.hpp"
#include <utility>

namespace yu::select::detail {

template <typename ResultPolicy, template <typename> typename OutcomePolicy, typename Subject>
class selection_performer {
    public:
        template <typename T>
        explicit selection_performer(T&& subject) : subject_(std::forward<T>(subject)) {}

        template <typename... Clauses>
        auto operator()(Clauses&&... clauses) && {
            return perform_selection<ResultPolicy, OutcomePolicy, Subject, Clauses...> //
                (std::forward<Subject>(subject_), std::forward<Clauses>(clauses)...);  //
        }

        template <typename... Clauses>
        auto operator()(Clauses&&...) & = delete;

    private:
        using captured_subject_t = capture_type_t<Subject>;

        captured_subject_t subject_;

        selection_performer(const selection_performer&) = delete;
        selection_performer(selection_performer&&)      = default;

        selection_performer& operator=(const selection_performer&) = delete;
        selection_performer& operator=(selection_performer&&)      = delete;
};

} // namespace yu::select::detail

#endif
