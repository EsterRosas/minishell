/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:52:57 by erosas-c          #+#    #+#             */
/*   Updated: 2023/09/30 11:24:26 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"

void	test(char *line)
{
	int i = 0;
	char **cmd;

	cmd = cmdtrim(line);
	/*while (cmd[i])
	{
		printf("trimmed[%i]: %s\n", i, cmd[i]);
		i++;
	}*/
	while (cmd[i])
		i++;
	cmd = cmdsubsplit(cmd, i);
	/*i = 0;
	while (cmd[i])
	{
		printf("splitted[%i]: %s\n", i, cmd[i]);
		i++;
	}*/
	cmd = cmdexpand(cmd, i);
	i = 0;
	while (cmd[i])
	{
		printf("home_expanded[%i]: %s\n", i, cmd[i]);
		i++;
	}
	/*while (cmd[i])
		i++;*/
	cmd = repl_var(cmd, i);
	i = 0;
	while (cmd[i])
	{
		printf("var_replcd[%i]: %s\n", i, cmd[i]);
		i++;
	}
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
