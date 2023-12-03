/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:52:57 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/02 17:05:34 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"

void	test(char *line, t_envv  *o_envp)
{
	int		i;
	char	**cmd_trm;
	char	**cmd_spl;
	char	**cmd_exp;
	char	**cmd_var;
	t_envv	*aux;

	aux = o_envp;
	(void)line;
	while (aux)
	{
		printf("aux->nm: %s, aux->val: %s\n", aux->nm, aux->val);
		aux = aux->next;
	}
	cmd_trm = cmdtrim(line);
/*	while (cmd_trm[i])
	{
		printf("trimmed[%i]: %s\n", i, cmd_trm[i]);
		i++;
	}
	free_all(cmd_trm, dbl_len(cmd_trm));*/
	cmd_spl = cmdsubsplit(cmd_trm);
/*	while (cmd_spl[i])
	{
		printf("splitted[%i]: %s\n", i, cmd_spl[i]);
		i++;
	}
	free_all(cmd_spl, dbl_len(cmd_spl));*/
	cmd_exp = cmdexpand(cmd_spl);
/*	while (cmd_exp[i])
	{
		printf("home_expanded[%i]: %s\n", i, cmd_exp[i]);
		i++;
	}
	free_all(cmd_exp, dbl_len(cmd_spl));*/
	cmd_var = repl_var(cmd_exp, o_envp);
	i = 0;
	while (cmd_var[i])
	{
		printf("var_replcd[%i]: %s\n", i, cmd_var[i]);
		i++;
	}
	free_all(cmd_var, dbl_len(cmd_var));
}

/*
In interactive mode:
ctrl-C: displays a new prompt on a new line
ctrl-D: exits the shell
ctrl-\: does nothing

Comandos permitidos:
echo:   with option -n
cd:     with only a relative or absolute path
pwd:    with no options
export: with no options
unset:  with no options
env:    with no options or arguments
exit:   with no options
ls:     Lista los archivos y directorios en el directorio actual.
touch:  Crea un archivo vacío o actualiza la marca de tiempo de un archivo existente.
mkdir:  Crea uno o más directorios.
rmdir:  Elimina directorios vacíos.
rm:     Elimina archivos o directorios.
cp:     Copia archivos y directorios.
mv:     Mueve (o renombra) archivos y directorios.
cat:    Muestra el contenido de un archivo.
-------------------------------------------------------------------------------------------
more / less:    Permite ver el contenido de un archivo paginado, avanzando página por página.
head / tail:    Muestra las primeras/últimas líneas de un archivo.
grep:           Busca patrones en archivos.
find:           Busca archivos y directorios en un sistema de archivos.
chmod:          Cambia los permisos de acceso a archivos y directorios.
chown:          Cambia el propietario y/o grupo de un archivo o directorio.
ps:             Muestra información sobre los procesos en ejecución.
kill:           Termina procesos especificados.
top:            Muestra información en tiempo real sobre el uso del sistema y los procesos.
tar:            Archiva o desarchiva archivos.
wget / curl:    Descarga archivos desde Internet.
who:            Muestra quién está conectado.
history:        Muestra el historial de comandos ejecutados.
df:             Muestra el uso del espacio en disco.
du:             Muestra el uso del espacio en disco de un archivo o directorio.
sudo:           Ejecuta un comando con privilegios de superusuario.
*/
