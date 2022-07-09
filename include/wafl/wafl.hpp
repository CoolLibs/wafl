#pragma once

#include <algorithm>
#include <string>
#include <string_view>
#include <vector>
#include "sort_two_vectors.hpp"

// TOOD namespace wafl

enum class Matches {
    Strongly,
    Weakly,
    NotAtAll,
};

struct search_params {
    std::string_view input;
    std::string_view reference;
};

auto similarity(search_params) -> float;
auto similarity_match(search_params) -> Matches;

auto comparator_between_two_values(float first, float second) -> bool;
auto remove_NotAtAll_from_vector(float value) -> bool;

// Container == std::vector<std::string>
// StringGetter == [](const std::string& str) -> std::string_view { return str; }
template<typename Container, typename StringGetter> // assert StringGetter is a function from Container::value_type to std::string_view
auto search_results(std::string_view input, const Container& container, StringGetter&& get_string) -> Container
{
    auto               container_copy = container;
    std::vector<float> float_container;
    float_container.resize(container.size());
    std::transform(container.begin(), container.end(), float_container.begin(), [&](auto&& element) {
        return similarity({.input = input, .reference = get_string(element)});
    });
    auto test = std::remove_if(float_container.begin(), float_container.end(), remove_NotAtAll_from_vector);

    std::sort(
        SortHelper::ValueIterator<std::vector<float>, Container>{float_container.begin(), container_copy.begin()},
        SortHelper::ValueIterator<std::vector<float>, Container>{float_container.end(), container_copy.end()}
    );
    return container_copy;
}