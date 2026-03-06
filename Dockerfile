FROM alpine:3.19

RUN apk add --no-cache libc6-compat

COPY app /app

CMD ["/app"]
