#include "testing.h"

void	test_extract_dollar_key_values(t_state* state)
{
	t_test_run();

	typedef struct s_case
	{
		char *name;
		char *data;
		char *expected;
	} t_case;

	setenv("a", "TEST_DOLLAR_VALUE_A", 1);
	setenv("b", "TEST_DOLLAR_VALUE_B", 1);
	setenv("longdollarkey", "TEST_LONG_DOLLAR_VALUE", 1);
	setenv("underscore_dollar_key", "TEST_UNDERSCORE_DOLLAR_VALUE", 1);
	setenv("number123_dollar_key123", "TEST_NUMBER_DOLLAR_VALUE", 1);
	setenv("_start_underscore_dollar_key", "TEST_START_UNDERSCORE_DOLLAR_VALUE", 1);

	t_case test_cases[] = {
		{
			.name = "single dollar",
			.data = ft_strdup("rrrr$a'at'"),
			.expected = ft_strdup("rrrrTEST_DOLLAR_VALUE_A'at'"),
		},
		{
			.name = "multi dollar with single value",
			.data = ft_strdup("rrrr$a'at'$a"),
			.expected = ft_strdup("rrrrTEST_DOLLAR_VALUE_A'at'TEST_DOLLAR_VALUE_A"),
		},
		{
			.name = "multi dollar with multi value",
			.data = ft_strdup("rrrr$a'at'$b"),
			.expected = ft_strdup("rrrrTEST_DOLLAR_VALUE_A'at'TEST_DOLLAR_VALUE_B"),
		},
		{
			.name = "long dollar key",
			.data = ft_strdup("rrrr$longdollarkey'at'"),
			.expected = ft_strdup("rrrrTEST_LONG_DOLLAR_VALUE'at'"),
		},
		{
			.name = "underscore dollar key",
			.data = ft_strdup("rrrr$underscore_dollar_key'at'"),
			.expected = ft_strdup("rrrrTEST_UNDERSCORE_DOLLAR_VALUE'at'"),
		},
		{
			.name = "underscore dollar key with number",
			.data = ft_strdup("rrrr$number123_dollar_key123'at'"),
			.expected = ft_strdup("rrrrTEST_NUMBER_DOLLAR_VALUE'at'"),
		},
		{
			.name = "underscore dollar key at beginning",
			.data = ft_strdup("rrrr$_start_underscore_dollar_key'at'"),
			.expected = ft_strdup("rrrrTEST_START_UNDERSCORE_DOLLAR_VALUE'at'"),
		},
		{
			.name = "not exists dollar key",
			.data = ft_strdup("rrrr$not_exists_dollar_key123'at'"),
			.expected = ft_strdup("rrrr'at'"),
		},
		{
			.name = "not valid dollar key with space",
			.data = ft_strdup("rrrr$ 'at'"),
			.expected = ft_strdup("rrrr$ 'at'"),
		},
		{
			.name = "not valid dollar key test with numbers except 0 should give empty string 1",
			.data = ft_strdup("rrrr$1'at'"),
			.expected = ft_strdup("rrrr'at'"),
		},
		{
			.name = "not valid dollar key test with numbers except 0 should give empty string 5",
			.data = ft_strdup("rrrr$5'at'"),
			.expected = ft_strdup("rrrr'at'"),
		},
		{
			.name = "should give double dollar when there is double dollar side by side",
			.data = ft_strdup("prefix.$$.suffix"),
			.expected = ft_strdup("prefix.$$.suffix"),
		},
		{
			.name = "should give double dollar when there is double dollar side by side",
			.data = ft_strdup("prefix.$0.suffix"),
			.expected = ft_strdup("prefix../minishell.suffix"),
		},
	};

  int64_t size = sizeof(test_cases) / sizeof(t_case);
  int64_t i = 0;
  while (i < size) {
    t_case tc = test_cases[i];
    extract_dollar_key_values(&tc.data, state);
    expect_equal_str(tc.name, tc.data, tc.expected);
		i++;
  }

	t_test_end();
}

void	run_dollar_test(t_state *state)
{
	t_group_run();
	test_extract_dollar_key_values(state);
	t_group_finish();
}
