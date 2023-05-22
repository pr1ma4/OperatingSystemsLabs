#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>


GtkWidget *window;
GtkWidget *pid_entry, *adress_entry, *value_entry;
GtkWidget  *label5,*label7;

#define MODEL_NAME_STR "MemAvailable:    "

void write_b(GtkWidget *window, gpointer data)
{
    const char* pid = gtk_entry_get_text(pid_entry);
    const char* adress = gtk_entry_get_text(adress_entry);
    const char* d = gtk_entry_get_text(value_entry);

    char proc[100] = "/proc/";
    strcat(proc,pid);
    strcat(proc,"/mem");

    /* Открываем файл. */
    int f = open(proc, O_WRONLY);

    /* Смещаемся до нужного адреса. */
    lseek(f, strtol(adress,NULL,16), SEEK_SET);

    long result = strtol(d,NULL,10);
    /* Пишем нужные байты. */
    write(f,&result, sizeof(long));
}

void read_b(GtkWidget *window, gpointer data)
{
    const char* pid = gtk_entry_get_text(pid_entry);
    const char* adress = gtk_entry_get_text(adress_entry);
    const char* d = gtk_entry_get_text(value_entry);

    char buffer[1024];
    char proc[100] = "/proc/";
    strcat(proc,pid);
    strcat(proc,"/mem");

    /* Открываем файл. */
    int f = open(proc, O_RDONLY);

    /* Смещаемся до нужного адреса. */
    lseek(f, strtol(adress,NULL,16), SEEK_SET);

    char str[10];
    char str2[1024];
    long result = 0;
    /* Читаем нужные байты. */
    /* Пишем нужные байты. */
    read(f,&result, sizeof(long));
    snprintf(str, sizeof (str), "%u", result);
    gtk_label_set_text(label5,str);

    FILE *fd;

    fd = fopen("/proc/meminfo", "r");

    do {
        memset(buffer, 0, sizeof(buffer));
        if (fgets(buffer, sizeof(buffer), fd) != NULL) {
            if (strstr(buffer, MODEL_NAME_STR) != NULL) {
                //snprintf(str2, sizeof (str), "%u", buffer);
                gtk_label_set_text(label7,buffer);
            }
        }
    } while ((!feof(fd)) && (!ferror(fd)));


    gtk_widget_show_all(window);
}

void my_close_app(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    GtkWidget *write_button,*read_button;
    GtkWidget *label1, *label2, *label3, *label4,*label6;
    GtkWidget *hbox,*vbox1,*vbox2,*vbox3,*vbox4,*vbox5,*vbox6;


    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Laba 2 V-11");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 1);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(my_close_app), NULL);

    write_button = gtk_button_new_with_label("Write!");
    read_button = gtk_button_new_with_label("Read!");

    g_signal_connect(G_OBJECT(write_button), "clicked", G_CALLBACK(write_b), NULL);
    g_signal_connect(G_OBJECT(read_button), "clicked", G_CALLBACK(read_b), NULL);

    label1 = gtk_label_new("Enter PID:");
    label2 = gtk_label_new("Enter Adress:");
    label3 = gtk_label_new("Enter new value:");
    label4 = gtk_label_new("Present value:");
    label5 = gtk_label_new("0");
    label6 = gtk_label_new("Memory:");
    label7 = gtk_label_new("");

    pid_entry = gtk_entry_new();
    adress_entry = gtk_entry_new();
    value_entry = gtk_entry_new();

    hbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
    vbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    vbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    vbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    vbox4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    vbox5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    vbox6 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);

    gtk_box_pack_start(GTK_BOX(vbox1), label1, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(vbox1), pid_entry, TRUE, TRUE, 1);

    gtk_box_pack_start(GTK_BOX(vbox2), label2, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(vbox2), adress_entry, TRUE, TRUE, 1);

    gtk_box_pack_start(GTK_BOX(vbox5), label4, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(vbox5), label5, TRUE, TRUE, 1);

    gtk_box_pack_start(GTK_BOX(vbox3), label3, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(vbox3), value_entry, TRUE, TRUE, 1);

    //gtk_box_pack_start(GTK_BOX(vbox6), label6, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(vbox6), label7, TRUE, TRUE, 1);

    gtk_box_pack_start(GTK_BOX(vbox4), read_button, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(vbox4), write_button, TRUE, TRUE, 1);


    gtk_box_pack_start(GTK_BOX(hbox), vbox1, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(hbox), vbox2, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(hbox), vbox3, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(hbox), vbox5, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(hbox), vbox6, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(hbox), vbox4, TRUE, TRUE, 1);


    gtk_container_add(GTK_CONTAINER(window), hbox);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}