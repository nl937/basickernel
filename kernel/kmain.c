#include "../drv/fb.h"
#include "../drv/keyboard.h"
#include "../console/console.h"
#include "../io/io.h"
#include "../io/serial.h"
#include "interrupts.h"
#include "idt.h"

char* logo = "      :::::::::  :::    :::               ::::::::   :::::::: \n\
     :+:    :+: :+:   :+:               :+:    :+: :+:    :+: \n\
    +:+    +:+ +:+  +:+                +:+    +:+ +:+         \n\
   +#++:++#+  +#++:++   +#++:++#++:++ +#+    +:+ +#++:++#++   \n\
  +#+    +#+ +#+  +#+                +#+    +#+        +#+    \n\
 #+#    #+# #+#   #+#               #+#    #+# #+#    #+#     \n\
#########  ###    ###               ########   ########       \n";

void kmain(){
    console_clear();
    console_write(logo);
    console_write("[ OK ] GDT initialized by bootloader\n");
    idt_install();
    console_write("[ OK ] IDT loaded\n");
}