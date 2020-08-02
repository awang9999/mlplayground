def C(n, step, cnt, v, k):
    if cnt > n or step > n:
        return
    if cnt == n and len(v) == k:
        # if counter cnt reached n print the list
        print(v)
        return
    else:
        # else append the step size to list
        v.append(step)
        # increment the cnt by step and recurse
        C(n, step, cnt + step, v, k)
        # remove the last step item from list
        v.pop()
        # increment the step size and recurse
        C(n, step + 1, cnt, v, k)


C(13, 1, 0, [], 8)
