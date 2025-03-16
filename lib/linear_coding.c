#include <stddef.h>
#include <stdio.h>
#include "bitarray.h"
#include "linear_coding.h"

binary_matrix code_word(binary_matrix word, binary_matrix generator) {
  /* A COMPLETER ET MODIFIER */
  return multiply_matrices(word,generator);
}

binary_matrix transposed_control_matrix(binary_matrix generator) {
  /* A COMPLETER ET MODIFIER */
  int row = nb_rows(generator);
  int col = nb_columns(generator);
  binary_matrix g = zero_matrix(col, col - row);
  int i;
  int j ;
  for(i = 0;i<row; i++){
    for(j = 0; j<col; j++){
       int col_index = j - row;
        if (col_index >= 0) {
            set_matrix_value(g, i, col_index, matrix_value(generator, i, j));
        }
    }
  }
  int l = 0;
  int k;
  for (k = row;k<col;k++){
      set_matrix_value(g,k,l,1);
      l++;
  }
 return g;

}

binary_matrix syndrome(binary_matrix word, binary_matrix tH) {
  /* A COMPLETER ET MODIFIER */
  return multiply_matrices(word, tH);
}

binary_matrix correct_result(binary_matrix word, binary_matrix s, binary_matrix tH) {
  /* A COMPLETER ET MODIFIER */
  if(is_zero_matrix(s)){
    return NULL;
  }
  int i,j, val;
  binary_matrix result;
  result = copy_matrix(word);
  for(i=0; i<nb_rows(tH); i++){
    binary_matrix row;
    row = zero_matrix(1, nb_columns(tH));
    for(j=0; j<nb_columns(tH); j++){
      set_matrix_value(row, 0, j, matrix_value(tH, i, j));
    }
    if(equals_matrix(row, s)){
      val = matrix_value(word, 0, i);
      if(val == 0){
        set_matrix_value(result, 0, i, 1);
      }else{
        set_matrix_value(result, 0, i, 0);
      }
    }
  }
  return result;
}

binary_matrix decode_word(binary_matrix word, binary_matrix tH) {
  /* A COMPLETER ET MODIFIER */
  binary_matrix s, corrected,result;
  s = syndrome(word, tH);
  corrected = correct_result(word, s, tH);
  int n,k,i;
  n = nb_rows(tH);
  k = nb_columns(tH);
  result = zero_matrix(1, n-k);

  if(corrected){
    for(i=0; i<n-k; i++){
      set_matrix_value(result, 0, i, matrix_value(corrected, 0, i));
    }
  }else{
    for(i=0; i<n-k; i++){
      set_matrix_value(result, 0, i, matrix_value(word, 0, i));
    }
  }
  return result;

}

void linear_encoding(binary_matrix generator) {
  int byte;
  buffer_t read_buffer, write_buffer;
  
  read_buffer.bits = init_bitarray();
  read_buffer.size = 0;
  write_buffer.bits = init_bitarray();
  write_buffer.size = 0;

  while ((byte = getchar()) !=  EOF) {
    add_byte(read_buffer.bits, read_buffer.size, byte);
    read_buffer.size += 8;
    encode_with_buffer(&read_buffer, &write_buffer, generator);
    while (write_buffer.size >= 8) {
      putchar(pop_byte(write_buffer.bits));
      write_buffer.size -= 8;
    }
  }

  /* Completion */
  set_bit(read_buffer.bits, read_buffer.size);
  read_buffer.size += nb_rows(generator) - read_buffer.size;
  encode_with_buffer(&read_buffer, &write_buffer, generator);
  while (write_buffer.size >= 8) {
    putchar(pop_byte(write_buffer.bits));
    write_buffer.size -= 8;
  }

  /* Completion for write_buffer */
  set_bit(write_buffer.bits, write_buffer.size);
  write_buffer.size += 8 - write_buffer.size;
  putchar(pop_byte(write_buffer.bits));
}

void encode_with_buffer(buffer_t *read_buffer, buffer_t *write_buffer, binary_matrix generator) {
  binary_matrix word;
  binary_matrix coded;
  while(read_buffer->size >= nb_rows(generator)) {
    word = pop_matrix_from_bitarray(read_buffer->bits, nb_rows(generator));
    read_buffer->size -= nb_rows(generator);

    //    print_matrix(word);
    /* v' = v*G */
    coded = code_word(word, generator);
    //    print_matrix(coded);
    write_buffer->size += append_matrix_to_bitarray(write_buffer->bits, coded, write_buffer->size);
  }
}

void linear_decoding(binary_matrix tH) {
  int byte;
  buffer_t read_buffer, write_buffer;
  
  read_buffer.bits = init_bitarray();
  read_buffer.size = 0;
  write_buffer.bits = init_bitarray();
  write_buffer.size = 0;

  while ((byte = getchar()) !=  EOF) {
    add_byte(read_buffer.bits, read_buffer.size, byte);
    read_buffer.size += 8;
    decode_with_buffer(&read_buffer, &write_buffer, tH, 2);
    while (write_buffer.size >= 8) {
      putchar(pop_byte(write_buffer.bits));
      write_buffer.size -= 8;
    }
  }

  add_byte(read_buffer.bits, read_buffer.size, byte);
  read_buffer.size += 8;
  while (get_bit(read_buffer.bits, read_buffer.size-1) == 0)
    read_buffer.size--;
  read_buffer.size--;
  decode_with_buffer(&read_buffer, &write_buffer, tH, 1);
  while (get_bit(write_buffer.bits, write_buffer.size-1) == 0)
    write_buffer.size--;
  write_buffer.size--;
  while (write_buffer.size >= 8) {
    putchar(pop_byte(write_buffer.bits));
    write_buffer.size -= 8;
  }
}

void decode_with_buffer(buffer_t *read_buffer, buffer_t *write_buffer, binary_matrix tH, int nb) {
  binary_matrix word;
  binary_matrix decoded;
  while(read_buffer->size >= nb*nb_rows(tH)) {
    word = pop_matrix_from_bitarray(read_buffer->bits, nb_rows(tH));
    read_buffer->size -= nb_rows(tH);

    //    print_matrix(word);
    /* v' = v*G */
    decoded = decode_word(word, tH);
    //    print_matrix(decoded);
    write_buffer->size += append_matrix_to_bitarray(write_buffer->bits, decoded, write_buffer->size);
  }
}
