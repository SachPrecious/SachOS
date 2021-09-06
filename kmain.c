    #include "drivers/frame_buffer.h"
    #include "drivers/serial_port.h"
    #include "drivers/io.h"
    #include "segmentation/segments.h"
    #include "interrupts/interrupts.h"
    #include "interrupts/keyboard.h"
    #include "interrupts/pic.h"
    #include "multiboot.h"
    #include "memory/paging/paging.h"
    
    
void init()
{
    
   segments_install_gdt();
   interrupts_install_idt();
   init_paging();
}
    
    
    
    
    int kmain(unsigned int ebx)
    {
       //char arr[] = "Welcome to SachOS";
       //fb_write(arr, 20);
       //serial_configure(SERIAL_COM1_BASE, Baud_115200);
       //serial_write(SERIAL_COM1_BASE, arr, 20);
       init();

       //serial_write(0x3F8, arr, 4);
       

       // fb_write_cell(0, 'A', FB_GREEN, FB_DARK_GREY);
       //fb_move_cursor(00);
       
      multiboot_info_t *mbinfo = (multiboot_info_t *) ebx;
      multiboot_module_t* modules = (multiboot_module_t*) mbinfo->mods_addr; 
      unsigned int address_of_module = modules->mod_start;

      if((mbinfo->mods_count) == 1){
         char str[] = "Module successfully loaded";
         serial_write(str,sizeof(str));
         
         typedef void (*call_module_t)(void);
            call_module_t start_program = (call_module_t) address_of_module;
            start_program();
      }
      else{
         char str[] = "Multiple modules loaded";
         serial_write(str,sizeof(str));
      }

      return 0;
            
       
       
       
    }
    
    
 
