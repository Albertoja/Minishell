#include "minishell.h"

int	ft_len_equal(char *str, char a)
{
	int	ret;

	ret = 0;
	while (*str != a && *str != '\0')
	{
		ret++;
		str++;
	}
	//write(1, "x", 1);
	return (ret);
}

int	ft_comp_var(char *cmds, char **env)
{
	int	len;
	int	ret;

	ret = 0;
	while (env[ret])
	{
		len = ft_len_equal(env[ret], '=');
		if (ft_strncmp(cmds, env[ret], len) == 0)
			return (ret);
		ret++;
	}
	return (0);
}

int	ft_check_export(char *str)
{
	while (*str)
	{
		if ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z') || (*str == '=') || (*str == '_'))
			str++;
		else
			return (0);
	}
	return (1);
}
static char	**copy_str_matrix(char **env, char *str, int a)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = malloc(sizeof(char *) * (count_str(env) + 2));
	while (env[++i])
	{
		if (i == a && a != 0)
			new_env[i] = ft_strdup(str);
		else
			new_env[i] = ft_strdup(env[i]);
	}
	if (a == 0)
		new_env[i] = ft_strdup(str);
	new_env[++i] = NULL;
	//ft_free_matrix(env);
	return (new_env);
}

char	**ft_export(char **cmds, char **env)
{
	int	cont;
	int	cont2;
	int	cop;

	cop = 0;
	cont2 = 1;
	cont = 0;
	if (!cmds[1] || !cmds || !*cmds)
	{
		while(env[cont])
		{
			printf("declare -x %s\n", env[cont]);
			cont++;
		}
		return (env);
	}
	while(cmds[cont2])
	{
		if (ft_check_export(cmds[cont2]) == 0)
		{
			printf("export: `%s': not a valid identifier\n", cmds[cont2]);
			exit(0);
		}
		cop = ft_comp_var(cmds[cont2], env);
		printf("------>%i\n", cop);
		env = copy_str_matrix(env, cmds[cont2], cop);
		cont2++;
	}
	return (env);
}
 