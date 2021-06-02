{This program uses a linked list to emulate adding and deleting
a song from the playlist of a media player.}

program PBL_2021;

const null_pointer = -1;
      list_size = 10;

var song_list : array[0..list_size - 1] of string;
    {store the song's name}
    next_pointer : array[0..list_size - 1] of integer;
    {store the pointer to next node}
    head_pointer : integer;
    {the starting of the link list}
    new_song, old_song : string;
    option : integer;

{initialise the array of the song list}
procedure init_list();
var i : integer;
begin
   head_pointer := 0;
   for i := 0 to list_size - 1 do
   begin
      song_list[i] := '';
      next_pointer[i] := null_pointer;
   end;
end;

{searching the location of the target song}
function search_list(target_item : string) : integer;
var current_pointer : integer;
    target_found : boolean;
begin
   {Assign the head pointer to current pointer so that
   searching starts from the head of the linked list}
   current_pointer := head_pointer;
   target_found := false;

   while (target_found = false) and (current_pointer <> null_pointer) do
     begin
      if (song_list[current_pointer] = target_item) then
         target_found := true
      else
         {If the item pointed by current pointer is not found,
         advance the current pointer to the next node by assigning
         the next pointer to the current pointer}
         current pointer := next_pointer[current_pointer]
     end;

   if target_found then
     search_list := current_pointer
   else
     search_list := null_pointer;
end;

procedure insert_to_front(new_item : string);
var index : integer;
    insert_point_found : boolean;
begin
   if song_list[head_pointer] = '' then
      {The linked list is an empty list, so the new item is added as a
      first data item}
      song_list[head_pointer] := new item
   else
   begin
      index := 0;
      insert_point_found := false;

      While (insert_point_found = false) and (index <> list_size) do
        begin
         index := index + 1;
         {Search for an empty location in the array}
         if song_list[index] = '' then
           begin
              song_list[index] := new_item;
              {Re-direct the next pointer}
              next_pointer[index := head_pointer;
              {Re-direct the head pointer to point to the newly added node}
              head_pointer := index;
              insert_point_found := true;
           end;
        end;

   end;
end;

{do at home}
procedure insert_after(after_item, new_item : string);
var current_pointer, index : integer;
    insert_point_found : boolean;
begin
   {Look for the correct insertion point  i.e. call function}
   current_pointer := search_list(after_item);

   if current_pointer <> null_pointer then
   begin
      index := 0;
      insert_point_found := ;

      while (insert_point_found = false) and (index <> list_size) do
        begin
         index := index + 1;
         {Search for an empty location in the array}
         if song-list[index] = '' then
         begin
            insert_point_found = true
            {The pointer of the newly added node is made to point to
            the node pointed by the original preceding node}
            next_pointer[index] := current_pointer;

            {Re-direct the pointer of the node at the insertion point
            to point to the newly added node}
            next_pointer[current_pointer] := index;

//
         end;
       end;

   end
   else
      writeln('Attempt to insert to a non-existent item');
end;
procedure insert_after(after_item, new_item : string);
var current_pointer, index : integer;
    insert_point_found : boolean;
begin
   {Look for the correct insertion point}
//

   if current_pointer <> null_pointer then
   begin
      index := 0;
//      insert_point_found := ;

//      while () and () do
        begin
         index := index + 1;
         {Search for an empty location in the array}
//         if  then
         begin
//
            {The pointer of the newly added node is made to point to
            the node pointed by the original preceding node}
//          next_pointer[index] := ;

            {Re-direct the pointer of the node at the insertion point
            to point to the newly added node}
//          next_pointer[current_pointer] := ;

//
         end;
       end;

   end
   else
      writeln('Attempt to insert to a non-existent item');
end;

procedure delete_from_front();
begin
   if song_list[haed_pointer] <> '' then
      {Re-driect the head pointer to point to the node orginally pointed
      by the node in front of the linked list}
      head_pointer := next_pointer[head_pointer]
   else
      writeln('Attempt to delete an empty list');
end;

procedure delete_node(item_to_be_deleted : string);
var current_pointer, index : integer;
    delete_point_found : boolean;
begin
   current_pointer := head_pointer;
   delete_point_found := false;

   While (delete_point_found = false) and (index <> list_size) do
   begin
      {Look for the node preceding the "node-to-be-deleted"}
      if (song_list[index] = item_to_be_deleted) then
      begin
       index := 0;
         if index <> null_pointer then
         begin
            {Store the pointer of the "node-to-be-deleted"}

            {Re-direct the pointer of the node preceding the
            "node-to-be-deleted" to point to the node originally after the
            "node-to-be-deleted}
//

            next_pointer[current_pointer] := ;
         end
         else
            writeln('Attempt to delete a non-existent item');
            delete_point_found := true;
      end
      else
         current_pointer := ;
     end;

end;

procedure show_list();
var current_pointer : integer;
begin
   current_pointer := head_pointer;
   while (current_pointer <> null_pointer) do
     begin
      writeln(song_list[current_pointer]);
      current_pointer := current_pointer + 1;
     end;
   writeln;
end;


{main program}
begin
   init_list();

// use the procedures and function above to complete the main program.
   writeln('1: Insert a song');
   writeln('2: Delete a song');
   writeln('3: Show the whole song');
   writeln('4: Quit the program');
   write('Enter your opiton: ');
   readln(option);
   if option = 1 then
   begin
      writeln('1: Insert to the front of the list');
      writeln('2: Insert after a song');
      write('Enter your opiton: ');
      readln(option);
      if option = 1 then
      begin
          write('Enter the name of the new song: ');
          readln(new_song);
          insert_to_front(new_song);
      end;
      else
      if option = 2 then
      begin
          write('Enter the name of the new song: ');
          readln(new_song);
          write('Enter the name of the previous song: ');
          readln(old_song);
          insert_after(old_song, new_song);
      end;
   end;
   else
   if option = 2 then
   begin
      writeln('1: Delete the front song of the list');
      writeln('2: Delete a song after a song');
      write('Enter your opiton: ');
      readln(option);
      if option = 1 then
         delete_from_front();
      else
      if option = 2 then
      begin
         write('Enter the name of the song to be deleted: ');
         readln(new_song);
         delete_node(new_song);
         insert_after(old_song, new_song);
      end;
   end;
   else
   if option = 3 then
      show_list();
   else
   if option = 4 then

   else
       writeln('Only 1-4 is allowed!');
   readln;
end.




