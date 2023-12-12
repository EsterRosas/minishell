/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:52:57 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/12 20:52:52 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	test(char *line, t_envv *o_envp)
{
	int		i;
	(void)o_envp;
//	char	**lexed;
	//t_cmd	*cmd;
	char	**trim;

//	lexed = repl_var(cmdexpand(cmdsubsplit(cmdtrim(line))), o_envp);
	i = 0;
	/* Before proceeding to PARSER we can check for syntax errors as we said.
	 * BUT!!!! E.g.: if using NON EXISTING COMMAND as first cmd->args item
	 * (cmd->args[0]), (> but so we need it parsed!!), then SHOW
	 * "minishell: non-existing_cmd: command not found"
	 */
	trim = cmdtrim(line);
	while (trim[i])
	{
		printf("trim[%i]: %s\n", i, trim[i]);
		i++;
	}
/*	cmd = parse_lexed(lexed, o_envp);
	printf("cmd->in: %i, cmd->out: %i, cmd->fl_p: %s\n", cmd->infile, cmd->outfile, cmd->full_path);
	while (cmd->args[i])
	{
		printf("cmd->args[%i]: %s\n", i, cmd->args[i]);
		i++;
	}
	free_all(cmd->args, dbl_len(cmd->args));
	free_cmds(lexed, cmd);
	free_all(lexed, dbl_len(lexed));*/
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
