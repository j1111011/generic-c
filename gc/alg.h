#ifndef GC_ALG_H
#define GC_ALG_H

#define gc_for_each_pos(_C, pos, range) \
    for ((pos) = _C##_range_begin(range); \
         (pos) != _C##_range_end(range); \
         _C##_forward(&(pos)))

#define gc_for_each_pos_rev(_C, pos, tmp, range) \
    for ((tmp) = _C##_range_end(range); \
         (tmp) != _C##_range_begin(range) ? (pos) = _C##_prev(tmp), 1 : 0; \
         _C##_backward(&(tmp)))

#define gc_for_each_pos_indexed(_C, i, pos, range) \
    for ((pos) = _C##_range_begin(range), (i) = 0; \
         (pos) != _C##_range_end(range); \
         _C##_forward(&(pos)), (i)++)

#define gc_for_each_pos_safe(_C, pos, tmp, range) \
    for ((pos) = _C##_range_begin(range), (tmp) = _C##_next(pos); \
         (pos) != _C##_range_end(range); \
         (pos) = (tmp), _C##_forward(&(tmp)))

#define gc_swap(_C, pos1, pos2) \
    do { \
        _C##_elem_t tmp = _C##_get(pos1); \
        _C##_set(pos1, _C##_get(pos2)); \
        _C##_set(pos2, tmp); \
    } while (0)

#define gc_for_each(_C, range, f) \
    do { \
        _C##_pos_t pos; \
        gc_for_each_pos(_C, pos, range) \
            (f)(_C##_get(pos)); \
    } while (0)

#define gc_find(_C, range, val, pos) \
    do { \
        gc_for_each_pos(_C, *(pos), range) { \
            if (_C##_get(*(pos)) == (val)) \
                break; \
        } \
    } while (0)

#define gc_find_eq(_C, range, eq, val, pos) \
    do { \
        gc_for_each_pos(_C, *(pos), range) { \
            if ((eq)(_C##_get(*(pos)), (val))) \
                break; \
        } \
    } while (0)

#define gc_find_if(_C, range, pred, pos) \
    do { \
        gc_for_each_pos(_C, *(pos), range) { \
            if ((pred)(_C##_get(*(pos)))) \
                break; \
        } \
    } while (0)

#define gc_count(_C, range, val, n) \
    do { \
        _C##_pos_t pos; \
        *(n) = 0; \
        gc_for_each_pos(_C, *(pos), range) { \
            if (_C##_get(*(pos)) == (val)) \
                (*(n))++; \
        } \
    } while (0)

#define gc_count_eq(_C, range, eq, val, n) \
    do { \
        _C##_pos_t pos; \
        *(n) = 0; \
        gc_for_each_pos(_C, *(pos), range) { \
            if ((eq)(_C##_get(*(pos)), (val))) \
                (*(n))++; \
        } \
    } while (0)

#define gc_count_if(_C, range, pred, n) \
    do { \
        _C##_pos_t pos; \
        *(n) = 0; \
        gc_for_each_pos(_C, *(pos), range) { \
            if ((pred)(_C##_get(*(pos)))) \
                (*(n))++; \
        } \
    } while (0)

#define gc_copy_front(_C1, range, _C2, cont, copy_elem) \
    do { \
        _C1##_pos_t pos; \
        gc_for_each_pos(_C1, pos, range) { \
            _C2##_insert_front(cont, (copy_elem)(_C1##_get(pos))); \
        } \
    } while (0)

#define gc_copy_front(_C1, range, _C2, cont, copy_elem) \
    do { \
        _C1##_pos_t pos; \
        gc_for_each_pos(_C1, pos, range) { \
            _C2##_insert_front(cont, (copy_elem)(_C1##_get(pos))); \
        } \
    } while (0)

#define gc_copy_before(_C1, range, _C2, cont, pos, copy_elem) \
    do { \
        _C1##_pos_t pos; \
        gc_for_each_pos(_C1, pos, range) { \
            _C2##_insert_before(cont, pos, (copy_elem)(_C1##_get(pos))); \
        } \
    } while (0)

#define gc_copy_after(_C1, range, _C2, cont, pos, copy_elem) \
    do { \
        _C1##_pos_t pos; \
        gc_for_each_pos(_C1, pos, range) { \
            _C2##_insert_after(cont, pos, (copy_elem)(_C1##_get(pos))); \
        } \
    } while (0)

#define gc_fill(_C, range, val) \
    do { \
        _C##_pos_t pos; \
        gc_for_each_pos(_C, pos, range) { \
            _C##_set(pos, val); \
        } \
    } while(0)

#define gc_generate(_C, range, generate_elem) \
    do { \
        int i; \
        _C##_pos_t pos; \
        gc_for_each_pos_indexed(_C, i, pos, range) { \
            _C##_set(pos, (generate_elem)(i)) \
        } \
    } while (0)

#endif
