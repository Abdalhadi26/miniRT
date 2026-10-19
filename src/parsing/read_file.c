/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 14:45:34 by ahhammad          #+#    #+#             */
/*   Updated: 2026/10/18 14:46:06 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int read_file(t_scene *scene, char *file_name)
{

    // return 0 if file is empty
    // return -1 if file cannot be opened
    // return -2 if there is an error reading the file
    // return -3 if there is an error parsing the file
    int fd;
    char *data;
    int ret;

    fd = open(file_name, O_RDONLY);
    data =  NULL;
    if (fd < 0)
    {
        ft_putstr_fd("Error: Failed to open the file.\n", 1);
        return (-1);
    }
    while (1)
    {
        //this will be inside a loop to read the file line by line and store it in data to be parsed later
        ret = get_next_line(fd, data);// read file line by line and store it in data to be parsed later
        //but if the file is empty, END of file, or there is an error reading the file, data will be NULL
        // and we will return 0 to indicate that there was an error reading the file 
        // so i have to differentiate between the three cases, if the file is empty, we will return 0,
        // if there is an error reading the file, we will return -1, and if we reach the end of the file, we will return 1
        // the data will send as paramter to gnl function, and returned value form gnl will be int
        if (ret == 0 && !data)
        {
            ft_putstr_fd("Error: The file is empty.\n", 1);
            close(fd);
            return (0);
        }
        else if (ret == -1)// if data != NULL, free it
        {
            if (data)
                free(data);
            ft_putstr_fd("Error: Failed to read the file.\n", 1);
            close(fd);
            return (-2);
        }
        
            //parse the data here
            //but first we have to check if the data is valid, if not, we will return -1
            //if the data is valid, we will parse it and store it in the scene struct
            //then we will free the data and continue reading the file
            //if the data is valid, we will return 1 to indicate that we have successfully read the file
            //and parsed it into the scene struct
            //if the data is invalid, we will return -1 to indicate that there was an error parsing the file
            //and we will free the data and return -1 to indicate that there was an error parsing the file
            //so i have to differentiate between the three cases, if the data is valid, we will return 1,
            //if the data is invalid, we will return -1, and if we reach the end of the file, we will return 0
            //the data will send as paramter to parse function, and returned value form parse function will be int
            ret = parse(scene, data);// free the data after parsing it inside the parse function, because we don't need it anymore
            if (ret == -1)
            {
                ft_putstr_fd("Error: Failed to parse the file.\n", 1);
                close(fd);
                return (-3);
            }
        
    }
    return (1);
}
