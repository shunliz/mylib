

HashTable* hash_table_create(DataDestroyFunc data_destroy, void* ctx, DataHashFunc hash, int slot_nr
)
{
    HashTable* thiz = NULL;

    return_val_if_fail(hash != NULL && slot_nr > 1, NULL);

    thiz = (HashTable*)malloc(sizeof(HashTable));

    if(thiz != NULL)
    {
        thiz->hash = hash;
        thiz->slot_nr  = slot_nr;
        thiz->data_destroy_ctx = ctx;
        thiz->data_destroy = data_destroy;
        if((thiz->slots = (DList**)calloc(sizeof(DList*)*slot_nr, 1)) == NULL)
        {
            free(thiz);
            thiz = NULL;
        }
    }

    return thiz;
}


Ret      hash_table_insert(HashTable* thiz, void* data)
{
    size_t index = 0;

    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    index = thiz->hash(data)%thiz->slot_nr;
    if(thiz->slots[index] == NULL)
    {
        thiz->slots[index] = dlist_create(thiz->data_destroy, thiz->data_destroy_ctx);
    }

    return dlist_prepend(thiz->slots[index], data);
}


Ret      hash_table_delete(HashTable* thiz, DataCompareFunc cmp, void* data)
{
    int index = 0;
    DList* dlist = NULL;

    return_val_if_fail(thiz != NULL && cmp != NULL, RET_INVALID_PARAMS);

    index = thiz->hash(data)%thiz->slot_nr;
    dlist = thiz->slots[index];
    if(dlist != NULL)
    {
        index = dlist_find(dlist, cmp, data);

        return dlist_delete(dlist, index);
    }

    return RET_FAIL;
}


Ret    hash_table_find(HashTable* thiz, DataCompareFunc cmp, void* data, void** ret_data)
{
    int index = 0;
    DList* dlist = NULL;
    return_val_if_fail(thiz != NULL && cmp != NULL && ret_data != NULL, RET_INVALID_PARAMS);

    index = thiz->hash(data)%thiz->slot_nr;
    dlist = thiz->slots[index];
    if(dlist != NULL)
    {
        index = dlist_find(dlist, cmp, data);

        return dlist_get_by_index(dlist, index, ret_data);
    }

    return RET_FAIL;
}


size_t   hash_table_length(HashTable* thiz)
{
    size_t i = 0;
    size_t nr = 0;

    return_val_if_fail(thiz != NULL, 0);

    for(i = 0; i < thiz->slot_nr; i++)
    {
        if(thiz->slots[i] != NULL)
        {
            nr += dlist_length(thiz->slots[i]);
        }
    }

    return nr;
}


Ret      hash_table_foreach(HashTable* thiz, DataVisitFunc visit, void* ctx)
{
    size_t i = 0;

    return_val_if_fail(thiz != NULL && visit != NULL, RET_INVALID_PARAMS);

    for(i = 0; i < thiz->slot_nr; i++)
    {
        if(thiz->slots[i] != NULL)
        {
            dlist_foreach(thiz->slots[i], visit, ctx);
        }
    }

    return RET_OK;
}


void hash_table_destroy(HashTable* thiz)
{
    size_t i = 0;

    if(thiz != NULL)
    {
        for(i = 0; i < thiz->slot_nr; i++)
        {
            if(thiz->slots[i] != NULL)
            {
                dlist_destroy(thiz->slots[i]);
                thiz->slots[i] = NULL;
            }
        }

        free(thiz->slots);
        free(thiz);
    }

    return;
}


